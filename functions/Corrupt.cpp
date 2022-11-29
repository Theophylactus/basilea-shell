#include "../Function.h"
#include "../Warningstream.h"
#include <random>
#include <stdexcept>
#include <fstream>
#include <iterator>
#include <vector>
#include <memory>

using std::string;

const Params_data Corrupt::params_data = {
										Param_data("input-filename", typeid(const char*)),
										Param_data("output-filename", typeid(const char*)),
										Param_data("bytes-to-remove", 5ULL)
										};
										
std::string Corrupt::run(Arglist& args) const {
	prepare_params(&args, params_data);

	string in_fname = args.next();
	
	// If the specified path is an HTTP URL, we download it using the download() function
	if(in_fname.find("http://") == 0 || in_fname.find("https://") == 0) {
		Arglist* params = new Arglist({in_fname});
		
		Function::instance_of("download")->run(*params);
		
		delete params;
		
		// Gets the file name from the URL where the file was downloaded from
		in_fname.erase(0, in_fname.rfind('/') + 1);
	}
	
	string out_fname = args.next();
	
	unsigned bytes_to_remove = std::stoi(args.next());
		
	// Reads the file bytes into a vector
	std::ifstream in(in_fname, std::ios::binary);
	if(!in)
		throw std::runtime_error("No se ha encontrado el archivo \"" + in_fname + "\"");

	std::vector<unsigned char>* bytes = new std::vector<unsigned char>(std::istreambuf_iterator<char>(in), {});
	in.close();
	
	srand(time(NULL));
	
	// Iterates over the vector and deletes random bytes; this is where the image is corrupted
	for(unsigned removed_count = 0; removed_count < bytes_to_remove;) {
		size_t vector_len = bytes->size();
		// We don't touch the first 100 bytes to prevent damaging the header
		for(size_t x = 50; x < vector_len - 50; ++x) {
			if(rand() % 1000 == 1) {
				bytes->erase(bytes->begin() + (rand() % vector_len) - 1);
				--vector_len;
				++removed_count;
			}
		}
	}
	
	// Writes the vector on a new file
	std::ofstream out(out_fname, std::ios::binary);
	if(in_fname == out_fname)
		general_warnstream << "Sobreescribiendo \"" + in_fname + "\"";
		
	for(unsigned char c : *bytes)
		out << c;
	out.close();
	
	delete bytes;
	
	return "true";
}
