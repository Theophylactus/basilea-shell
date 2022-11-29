#include "extra.h"
#include "Warningstream.h"
#include "variables.h"
#include "Function.h"
#include "parse_command.h"
#include <iostream>
#include <algorithm>
#include <vector>

using std::string;
using std::vector;

// Returns a vector containing all the commands in a script
// Remind that in the corresponding header, the last two parameters are defaulted to 0
vector<Command> get_script_commands(const string& script, size_t origin_line, size_t origin_col) {
	vector<Command> commands;
	
	std::pair<string::const_iterator, string::const_iterator> square_brackets;
	string::const_iterator f_bracket, l_bracket = script.begin();
	
	/* Finds all the commands in the script. Subcommands (commands inside other commands) are not parsed; rather, they're 
	 * replaces by their result later when running each super-command */
	while(true) {
		/* Gets the position of the command */
		square_brackets = extra::find_delimiters(l_bracket, script.end(), '[');
		f_bracket = square_brackets.first;
		l_bracket = square_brackets.second;
		
		if(f_bracket == script.end())
			break;
		
		/* Finds the line and column where the command starts */
		size_t line = origin_line;
		size_t col = origin_col;
		for(auto i = script.begin(); i != f_bracket; ++i) {
			++col;
			if(*i == '\n') {
				++line;
				col = 0;
			}
		}
		
		/* Appends the command to the vector */
		commands.emplace_back(string(f_bracket + 1, l_bracket), line, col);
	}

	return commands;
}


string parse_command(Command cmd) {
	Set::replace_vars_by_vals(&(cmd.text));
	
	const Function* func = Function::instance_of(cmd.get_function());
	
	Arglist args = cmd.get_args();
	
	try {		
		std::string result = func->run(args);
		
		// Displays the warnings that executing the command may have caused
		if(general_warnstream.has_any())
			std::cout << "Advertencia (" << cmd.get_function() << ")(Lin. " << cmd.line << ")(Col. " << cmd.col << ") " << general_warnstream.get_all();
		
		return result;
		
	} catch(const std::exception& ex) {
		std::cout << "Error fatal (" << cmd.get_function() + ")(Lin. " << cmd.line << ")(Col. " << cmd.col << ") " << ex.what() << "\n";
		exit(3);
	}
}
