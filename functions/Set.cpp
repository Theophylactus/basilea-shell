#include "../Function.h"
#include "../extra.h"
#include <map>
#include <stdexcept>
#include <iostream>

using std::string;

/* Where variables are stored, as name -> value */
std::map<string, string> vars;

const Params_data Set::params_data = {
										Param_data("name", typeid(const char*)),
										Param_data("value", typeid(const char*))
										};

string Set::run(Arglist& args) const {
	prepare_params(&args, params_data);
	
	string name = args.next();
	
	// Checks the name is valid
	for(auto it = name.begin(); it != name.end(); ++it) {
		if(!isalnum(*it) && *it != '-')
			throw std::runtime_error("El nombre de la variable solo puede contener carácteres alfanuméricos y guiones (-)");
	}
	
	vars[name] = args.next();
	
	return "";
}

void Set::replace_vars_by_vals(std::string* source) {
	for(auto const& pair : vars) {
		*source = extra::replace_all(*source, '$' + pair.first, pair.second);
	}
}
