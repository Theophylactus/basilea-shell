// Christus vincit + Christus regnat + Christus imperat

#pragma once

#include <typeinfo>
#include <string>
#include <vector>

class Param_data {
private:
	const char* name;
	bool required = false;
	const char* default_val;
	size_t t_hash;
	const char* t_name;
	
public:
	Param_data(const char* n, const std::type_info& val);
	Param_data(const char* n, const char* val);
	Param_data(const char* n, bool val);
	Param_data(const char* n, long double val);
	Param_data(const char* n, unsigned long long val);
	
	const char* get_def_val() const;
	
	/* Returns whether the given arg is of the type of this Param_data instance */
	bool matches_type(const std::string& arg) const;
	
	/* Returns the name of the parameter. (Used only for debugging in error messages) */
	const char* get_name() const noexcept {
		return name;
	}
	
	const char* type_name() const noexcept {
		return t_name;
	}
	
	bool is_required() const noexcept {
		return required;
	}
	
	const size_t type_hash() const noexcept {
		return t_hash;
	}
};

using Params_data = std::vector<Param_data>;
