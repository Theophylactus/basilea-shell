#include <unistd.h>
#include <vector>
#include <stdexcept>
#include "../Function.h"

const Params_data Wait::params_data = {
										Param_data("time-milliseconds", typeid(unsigned long long))
										};

std::string Wait::run(Arglist& args) const {
	prepare_params(&args, params_data);
	usleep(std::stol(args.next()) * 1000);
	return "";
}
