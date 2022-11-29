#pragma once

#include <queue>
#include <string>
#include <vector>

class Arglist : private std::queue<std::string> {
public:

	Arglist(const std::vector<std::string>& = {});
	
	void add(const std::string& arg);
	
	std::string next();
	
	bool hasnext() const noexcept;
	
	size_t length() const noexcept;
};
