#include "../Function.h"
#include <stdexcept>
#include <stdlib.h>
#include <limits.h>

/* Indeed, when we need more control over the contents of args, we don't handle it with prepare_params() */

std::string Random::run(Arglist& args) const {
	if(!args.hasnext())
		throw std::runtime_error("Debe especificar al menos 1 argumento, el del número máximo.");

	unsigned long long first = std::stoi(args.next());
	
	if(!args.hasnext())
		return std::to_string(rand() % first);
	
	unsigned long long second = std::stoi(args.next());
	return std::to_string(rand() % (second - first) + first);
}
