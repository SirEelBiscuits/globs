#include "../util/utility.h"

#include <string>
#include <fstream>

void ReadFile(char const* file, std::string& buffer) {
	std::ifstream f(file);

	char c = f.get();
	while(f.good()) {
		buffer.push_back(c);
		c = f.get();
	}
	return;
}

