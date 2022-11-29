#include "../Function.h"
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>

const Params_data Scp::params_data = {
										Param_data("item-code", typeid(unsigned long long))
										};


std::string Scp::run(Arglist& args) const {
	prepare_params(&args, params_data);
	
	struct stat info;
	if(stat("scp/", &info) != 0)
		throw std::runtime_error("No se ha encontrado la carpeta \"scp\". Descarge el archivo http://exerceo.uk.to/tabularium/scp.zip y descomprímalo en la carpeta donde se halle el archivo ejecutable de este programa.");
	        	
	std::string item = args.next();
	
	// Adds the needed zeros to the item code
	for(int t = item.length(); t < 3; ++t)
		item = "0" + item;
			
	item = "scp/SCP-" + item + ".txt";

	std::ifstream in(item);
	if(!in)
		throw std::runtime_error("No se ha podido encontrar el archivo \"" + item + "\". ");
	
	std::string line;
	std::stringstream content;
	while(getline(in, line))
		content << line << "\n";
	
	return content.str();
}
