#include "Arglist.h"
#include <map>

class variables {
private:
	static std::map<std::string, std::string> vars;
public:
	static std::string set(Arglist& name_and_val);
	
	static void replace_vars_by_vals(std::string* source);
};
