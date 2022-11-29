#include "Arglist.h"

using std::string;

Arglist::Arglist(const std::vector<string>& args) {
	for(const string& arg : args)
		push(arg);
}

void Arglist::add(const string& arg) {
	push(arg);
}

string Arglist::next() {
	string arg = front();
	pop();
	return arg;
}

bool Arglist::hasnext() const noexcept {
	return !empty();
}

size_t Arglist::length() const noexcept {
	return size();
}
