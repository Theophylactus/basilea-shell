#include "../Function.h"
#include <iostream>
#include "../extra.h"

using std::string;

/*static inline void parse_special_chars(string* str) {
	
}*/

const Params_data Echo::params_data = {
									Param_data("text", typeid(const char*))
									};

std::string Echo::run(Arglist& args) const {
	prepare_params(&args, params_data);
	
	while(args.hasnext()) {// Don't add a space if it's the last element
		string arg = args.next();
		arg = extra::replace_all(arg, "\\n", "\n");
		arg = extra::replace_all(arg, "\\b", "\b");
		arg = extra::replace_all(arg, "\\r", "\r");
		std::cout << arg << (args.hasnext() ? " " : "") << std::flush;
	}	
	
	return "";
}
