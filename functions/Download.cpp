#include "../Function.h"
#include <string>
#include <stdexcept>
#include "../extra.h"

using std::string;

/*
inline string URL_encode(string text) {
	stringstream result;
	for(size_t x = 0; x < text.length(); ++x) {
		char c = text.at(x)
		if(isalnum(c) || c == '-' || c == '.' || c == '_' || c == '~')
			result << c;
		else
			result << '%' << (int)c;
	}
	
	return result.str();
}*/


const Params_data Download::params_data = {
											Param_data("url", typeid(const char*))
											};

std::string Download::run(Arglist& args) const {
	prepare_params(&args, params_data);
	string URL = args.next();

	if(system(string("wget --no-check-certificate '" + extra::replace_all(URL, "'", "%27") + "'").c_str()) == -1)
		throw std::runtime_error("Ocurrió un error interno al descargar el archivo desde \"" + URL + "\"");
		
	return URL.substr(URL.rfind('/')+1, URL.length() - URL.rfind('/') - 1);
}
