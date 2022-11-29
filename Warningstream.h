#include <string>
#include <sstream>

class Warningstream {
private:
	std::stringstream contents;
	
public:
	std::string get_all();
	bool has_any() const;
	
	friend Warningstream& operator<<(Warningstream& warn, const std::string& message);
	friend Warningstream& operator<<(Warningstream& warn, const char* message);
	/* std::string and const char* aren't included in this template declaration (see how we declare them separately before)
	 * as they are const pass-by-reference. This template is not, as it is meant to be used in primary types */
	template<typename T> friend Warningstream& operator<<(Warningstream& warn, T w);
};

extern Warningstream general_warnstream;
