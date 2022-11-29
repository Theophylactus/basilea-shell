#include "variables.h"
#include "extra.h"
#include <stdexcept>
#include <iostream>

using std::string;

std::map<string, string> variables::vars;

string variables::set(Arglist& name_and_val) {
	if(name_and_val.length() < 1)
		throw std::runtime_error("Debe especificar el nombre de la variable");
	
	if(name_and_val.length() < 2)
		throw std::runtime_error("Debe especificar el valor de la variable");
	
	string name = name_and_val.next();
	
	// Checks the name is valid
	for(auto it = name.begin(); it != name.end(); ++it) {
		if(!isalnum(*it) && *it != '-')
			throw std::runtime_error("El nombre de la variable solo puede contener carácteres alfanuméricos y guiones (-)");
	}
	
	variables::vars[name] = name_and_val.next();
	
	return "";
}

void variables::replace_vars_by_vals(std::string* source) {
	for(auto const& pair : variables::vars) {
		*source = extra::replace_all(*source, '$' + pair.first, pair.second);
	}
}
