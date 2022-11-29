#include "Function.h"
#include <stdexcept>
#include <iostream>

void Function::prepare_params(Arglist* args, const Params_data& params_data) {
	Arglist args_read_copy = *args;
	
	// Per Param_data vector iteramus
	for(const Param_data& param_data : params_data) {
		// Parametrum vacans in argumentorum vectore!
		if(!args_read_copy.hasnext()) {
			if(param_data.is_required()) // ...et necessarium est
				throw std::runtime_error("The parameter \"" + std::string(param_data.get_name()) + "\" is required but it wasn't provided.");
			else // ...et optionale est. Tunc parametrum addimus
				args->add(param_data.get_def_val());
		}
		// Parametrum non vacans...
		else {
			// sed genere non concordat
			if(!param_data.matches_type(args_read_copy.next()))
				throw std::runtime_error("The argument given for \"" + std::string(param_data.get_name()) + "\" does not match the demanded type \"" + param_data.type_name() + "\"");
		}
	}
}

/*
 * Since Function::instance_of is going to be called a lot of times, we initialize the Function subclasses beforehand for then
 * returning the already initialized objects, therefore saving some resources in repeated object initializations and copying processes
 */
static const Compute compute;
static const Corrupt corrupt;
static const Download download;
static const Echo echo;
static const Integral integral;
static const Shell_exec shell_exec;
static const Plot plot;
static const Litaniae litaniae;
static const Scp scp;
static const Random rand_func; /* named like this to avoid conflict */
static const Write write;
static const Read read;
static const Scriptor scriptor;
static const Set set;
static const Wait wait;

const Function* Function::instance_of(const std::string& func) {
	if(func == "compute")
		return &compute;
	else if(func == "shell-exec")
		return &shell_exec;
	else if(func == "download")
		return &download;
	else if(func == "echo")
		return &echo;
	else if(func == "plot")
		return &plot;
	else if(func == "litaniae")
		return &litaniae;
	else if(func == "corrupt")
		return &corrupt;
	else if(func == "scp")
		return &scp;
	else if(func == "random")
		return &rand_func;
	else if(func == "write")
		return &write;
	else if(func == "read")
		return &read;
	else if(func == "integral")
		return &integral;
	else if(func == "set")
		return &set;
	else if(func == "scriptor")
		return &scriptor;
	else if(func == "wait")
		return &wait;
	else {
		std::cout << "Función desconocida.\n";
		exit(2);
	}
}
