#include "../util/utility.h"
#include "log.h"

#include <string>
#include <fstream>

void ReadFile(char const* file, std::string& buffer) {
	LOG_MSG("IO", "Reading file %s", file);
	std::ifstream f(file);

	char c = f.get();
	unsigned int size = 0;
	while(f.good()) {
		buffer.push_back(c);
		size++;
		c = f.get();
	}
	LOG_MSG("IO", "Read %u bytes", size);
	return;
}

