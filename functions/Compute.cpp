/*
 *                                            Ave, Iesu Christe
 *
 *                                                 ########
 *                                                 ########
 *                                                 ########
 *                                                 ########
 *                                                 ########
 *                                                 ########
 *                                  ######################################
 *                                  ######################################
 *                                  ######################################
 *                                  ######################################
 *                                                 ########
 *                                                 ########
 *                                                 ########
 *                                                 ########
 *                                                 ########
 *                                                 ########
 *                                                 ########
 *                                                 ########
 *                                                 ########
 *                                                 ########
 *                                                 ########
 *                                                 ########
 *                                                 ########
 *                                                 ########
 *                                                 ########
 *                                                 ########
 *                                                 ########
 *                                                 ########
 *
 *                                       In Honorem Mathematici Euleri
 */

#include <stdexcept>
#include <cmath>
#include <array>
#include <string.h>
#include "../extra.h"
#include "../Function.h"

using std::string;

inline string replace_once(string main_str, const string& target, const string& replacement) {
	if(main_str.find(target) != string::npos)
		main_str.replace(main_str.find(target), target.length(), replacement);
	
	return main_str;
}

long double factorial(long double n) {
	unsigned a = round(n);
	if(a == 1)
		return 1;
	else
		return a * factorial(a - 1);
}

inline void parse_constants(string* expression) {
	*expression = extra::replace_all(*expression, "PI", "3.1415926535897932384");
	*expression = extra::replace_all(*expression, "E", "2.7182818284590452353");
}

const std::array<string, 22> functions = {"sin", "asin", "cos", "acos", "tan", "atan", "cosh", "sinh",
										  "tanh", "acosh", "asinh", "atanh", "ln", "log", "sqrt",
										  "cbrt", "integral", "factorial", "round", "ceil", "abs", "floor"};
										
// Looks for functions in the term and computes them (example: "sqrt 100" turns into 10)
long double parse_functions(const string& term) {
	string function = "";
	long double term_number = 0, result;
	
	// Gets the function in the term (acos -48)
	for(size_t x = 0; x < functions.size(); ++x) {
		if(term.find(functions.at(x)) == 0) {
			function = functions.at(x);
			break;
		}
	}
	try {
		term_number = std::stold(replace_once(term, function, ""));
	} catch(...) { } // Thrown if the term has non-numerical characters which are not the function itself (example: ln 100hello)
	
		
	if(function == "sin")
		result = sin(term_number);
		
	else if(function == "asin")
		result = asin(term_number);
		
	else if(function == "cos")
		result = cos(term_number);
		
	else if(function == "acos")
		result = acos(term_number);
		
	else if(function == "tan")
		result = tan(term_number);
		
	else if(function == "atan")
		result = atan(term_number);
		
	else if(function == "cosh")
		result = cosh(term_number);
		
	else if(function == "sinh")
		result = sinh(term_number);
		
	else if(function == "tanh")
		result = tanh(term_number);
		
	else if(function == "acosh")
		result = acosh(term_number);
		
	else if(function == "asinh")
		result = asinh(term_number);
		
	else if(function == "atanh")
		result = atanh(term_number);
		
	else if(function == "ln")
		result = log(term_number);
		
	else if(function == "log")
		result = log10(term_number);
		
	else if(function == "sqrt")
		result = sqrt(term_number);
		
	else if(function == "cbrt")
		result = cbrt(term_number);

	else if(function == "factorial")
		result = factorial(term_number);
		
	else if(function == "round")
		result = roundl(term_number);
		
	else if(function == "ceil")
		result = ceil(term_number);
		
	else if(function == "abs")
		result = term_number < 0 ? -1 * term_number : term_number;
		
	else if(function == "floor")
		result = floor(term_number);
	
	else
		// When no function is found, the result is set to the number
		result = term_number;
		
	return result;
}


// The order of the operators matters, as it keeps the hierarchy of mathematical operations
const char* operators = "+#^*/";

// This finds the first operator of a string
inline char find_expression_operator(const string& expr) {
	for(unsigned x = 0; x < strlen(operators); ++x)
		for(unsigned y = 0; y < expr.length(); ++y)
			if(expr.at(y) == operators[x])
				return operators[x];

	return 'E'; // The default value is 'E', when it is returned, it means that the operator was not found
}

// This method by itself cannot do substractions nor interpret constants
long double compute(string expression) {
	// Parses brackets
	if(count_char(expression, '(') > 0 && (count_char(expression, '(') == count_char(expression, ')'))) {
		auto delimiting_parentheses = extra::find_delimiters(expression.begin(), expression.end(), '(');
		auto f_bracket = delimiting_parentheses.first;
		auto l_bracket = delimiting_parentheses.second;
		/* Subexpression delimited by the parentheses */
		string sub_expr = std::string(f_bracket + 1, l_bracket);

		return compute(expression.replace(f_bracket, l_bracket + 1, std::to_string(compute(sub_expr))));
	}
	
	// The first hierarchical operator inside the expression (e.g. '-' in 5*5-3)
	const char operador = find_expression_operator(expression);

	// The numbers after and before the operator
	string first_term_str = expression.substr(0, expression.find(operador));
	string second_term_str = expression.substr(expression.find(operador) + 1, expression.length() - expression.find(operador)-1);

	long double first_term = 0, second_term = 0;
	
	// If the first and/or second term is an expression, it is computed
	// The if() could be removed and just do compute() alone, but if the term is a number (not an expressionession),
	// the compute() function would be executed for nothing, which would slightly decrease performance
	if(find_expression_operator(first_term_str) != 'E')
		first_term = compute(first_term_str);
	else
		first_term = parse_functions(first_term_str);
		
	if(find_expression_operator(second_term_str) != 'E')
		second_term = compute(second_term_str);
	else
		second_term = parse_functions(second_term_str);


	long double value = 0;
	switch(operador) {
		case '*':
			value = first_term * second_term;
		break;
		case '/':
			value = first_term / second_term;
		break;
		case '+':
			value = first_term + second_term;
		break;
		case '#': // Hash is used internally to distinguish substraction from negative numbers
			value = first_term - second_term;
		break;
		case '^':
			value = pow(first_term, second_term);
		break;
		default:
			// The return value is set to the first term, because it likely will be just a number without operators
			value = first_term;
	}

	return value;
}


const Params_data Compute::params_data = {
										Param_data("expression", typeid(const char*))
										};

/* static constexpr size_t Function::return_type = typeid(long double).hash_code(); */

std::string Compute::run(Arglist& args) const {
	prepare_params(&args, params_data);
	
	string expression = extra::replace_all(args.next(), " ", "");
	parse_constants(&expression);
	
	// This replaces substraction signs (number1-number2) by hashes to distinguish them from
	// negative signs (-number). We don't want the program to split expressions in such signs.
	for(unsigned x = 1; x < expression.length(); ++x)
		if(expression.at(x) == '-')
			if(std::isdigit(expression.at(x - 1)))
				expression = expression.replace(x, 1, "#");
				
	return std::to_string(compute(expression));
}
