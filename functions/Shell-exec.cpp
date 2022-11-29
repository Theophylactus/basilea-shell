#include "../Function.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <sstream>


const Params_data Shell_exec::params_data = {
											Param_data("bash-command", typeid(const char*))
											};
	

std::string Shell_exec::run(Arglist& args) const {
	prepare_params(&args, params_data);
	
	const char* command = args.next().c_str();
	
	std::array<char, 128> buffer;
	std::stringstream result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);
	if (!pipe) {
		throw std::runtime_error("Error interno: popen() falló");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result << buffer.data();
	}
	return result.str();
}
