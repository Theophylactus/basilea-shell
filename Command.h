#pragma once

#include "Arglist.h"
#include "Function.h"

struct Command {
	std::string text;
	size_t line;
	size_t col;
	
	Command(const std::string& txt, size_t l, size_t c);
	
	Arglist get_args() const;
	
	std::string get_function() const;
};
