#include "../Function.h"
#include <fstream>
#include <string>
#include <sstream>

const Params_data Read::params_data = {
										Param_data("filename", typeid(const char*))
										};
											
std::string Read::run(Arglist& args) const {
	prepare_params(&args, params_data);
	
	std::ifstream ifs(args.next());
	return std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
}
