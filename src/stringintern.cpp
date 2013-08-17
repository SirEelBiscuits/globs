#include "stringintern.h"

std::vector<std::string> StringIntern::s_strings;

StringIntern StringIntern::Create(std::string fromString) {
	for( int i = s_strings.size() - 1; i >= 0; --i ) {
		if( s_strings[i].compare( fromString ) == 0 ) {
			return StringIntern(i);
		}
	}
	s_strings.push_back(fromString);
	return StringIntern(s_strings.size() - 1);
}

StringIntern::StringIntern(int idx)
	: idx(idx)
{}

bool StringIntern::operator==(StringIntern& rhs) const {
	return idx == rhs.idx;
}

/*
StringIntern::operator char const* const() const {
	return s_strings[idx].c_str();
}
*/

StringIntern::operator char const*() const {
	return s_strings[idx].c_str();
}

char const* const StringIntern::toString() const {
	return s_strings[idx].c_str();
}

StringIntern operator"" _i(char const* in) {
	return StringIntern::Create(in);
}

std::ostream& operator<<(std::ostream& os, StringIntern& si) {
	return os << StringIntern::s_strings[si.idx];
}
