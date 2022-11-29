#include "../Function.h"
#include <fstream>
#include <string>
#include <sstream>

const Params_data Write::params_data = {
										Param_data("output-filename", typeid(const char*)),
										Param_data("contents", typeid(const char*))
										};

std::string Write::run(Arglist& args) const {
	prepare_params(&args, params_data);
	
	std::string out_filename = args.next();
	std::ofstream out_file(out_filename, std::ios::app);
	out_file << args.next();
	out_file.close();
	
	return out_filename;
}
