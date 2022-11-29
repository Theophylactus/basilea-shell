#include "Param_data.h"
#include <string>
#include <stdexcept>

// If argument given as default value is a type_info object, we interpret that that means the data type
// was provided instead of the default value. Thus, there is no default value, hence the parameter is required
Param_data::Param_data(const char* n, const std::type_info& type) 
 : name(n), required(true), t_hash(type.hash_code()), t_name(type.name()) { }

// String (as const char*)
Param_data::Param_data(const char* n, const char* def_val)
 : name(n), default_val(def_val), t_hash(typeid(const char*).hash_code()), t_name("string") { }

// Boolean
Param_data::Param_data(const char* n, bool def_val)
 : name(n), default_val(def_val ? "true" : "false"), t_hash(typeid(bool).hash_code()), t_name("boolean") { }

// Long double
Param_data::Param_data(const char* n, long double def_val)
 : name(n), default_val(std::to_string(def_val).c_str()), t_hash(typeid(long double).hash_code()), t_name("long double") { }

// Unsigned long long
Param_data::Param_data(const char* n, unsigned long long def_val)
 : name(n), default_val(std::to_string(def_val).c_str()), t_hash(typeid(unsigned long long).hash_code()), t_name("unsigned long long") { }


const char* Param_data::get_def_val() const {
	if(required)
		throw std::runtime_error("Error: the parameter \"" + std::string(name) + "\" is a required parameter, so it has not default value.");
	else
		return default_val;
}

/* Checks wheter a given string can be casted into the data type of this Param_data */
bool Param_data::matches_type(const std::string& arg) const {
	// /*DEBUG*/ std::cout << "I am " << name << ", of type " << t_name << ", with the hash " << t_hash << std::endl;
	
	if(t_hash == typeid(const char*).hash_code())
		return true;
	
	else if(t_hash == typeid(unsigned long long).hash_code()) {
		for(size_t x = 0; x < arg.length(); ++x) {
			if(!isdigit(arg.at(x)))
				return false;
		}
		return true;
	}
	else if(t_hash == typeid(long double).hash_code()) {
		char* endptr = 0;
		strtold(arg.c_str(), &endptr);
		
		if(*endptr != '\0')
			return false;
				
		return true;
	}	
	else if(t_hash == typeid(bool).hash_code()) {
		if(arg == "true" || arg == "false" || arg == "0" || arg == "1")
			return true;
		
		return false;
	}
	else
		throw std::runtime_error("Fatal internal error: a Param_data object with an unrecognized data type has been initialized. Look for ill-formed Params_data vectors in function definition files");
}
