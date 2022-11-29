#include "Warningstream.h"
#include <string>
#include <sstream>

std::string Warningstream::get_all() {
	std::string w = contents.str();
	contents.str("");
	return w;
}

bool Warningstream::has_any() const {
	return contents.rdbuf()->in_avail() != 0;
}

Warningstream& operator<<(Warningstream& warn, const std::string& message) {
	warn.contents << message << "\n";
	return warn;
}
Warningstream& operator<<(Warningstream& warn, const char* message) {
	warn.contents << message << "\n";
	return warn;
}

template<typename T> Warningstream& operator<<(Warningstream& warn, T message) {
	warn.contents << message << "\n";
	return warn;
}
template Warningstream& operator<< <int>(Warningstream& warn, int w);
template Warningstream& operator<< <unsigned>(Warningstream& warn, unsigned w);
template Warningstream& operator<< <double>(Warningstream& warn, double w);
template Warningstream& operator<< <float>(Warningstream& warn, float w);
template Warningstream& operator<< <char>(Warningstream& warn, char w);
template Warningstream& operator<< <bool>(Warningstream& warn, bool w);

Warningstream general_warnstream;
