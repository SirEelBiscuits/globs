#include "../util/stringintern.h"

std::vector<std::string> StringIntern::s_strings;

int const StringIntern::CreateInternal(std::string fromString) {
	for(int i = s_strings.size() - 1; i >= 0; --i) {
		if(s_strings[i].compare(fromString) == 0) {
			return i;
		}
	}
	s_strings.push_back(fromString);
	return s_strings.size() - 1;
}

StringIntern::StringIntern(int idx)
	: idx(idx)
{}

StringIntern::StringIntern(std::string fromString)
	: idx(CreateInternal(fromString))
{}

bool StringIntern::operator==(StringIntern& rhs) const {
	return idx == rhs.idx;
}

StringIntern::operator char const*() const {
	return s_strings[idx].c_str();
}

char const* const StringIntern::toString() const {
	return s_strings[idx].c_str();
}

StringIntern operator"" _i(char const* in, size_t numChars) {
	return StringIntern(std::string(in, numChars));
}

std::ostream& operator<<(std::ostream& os, StringIntern& si) {
	return os << si.toString();
}
