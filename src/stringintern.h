#pragma once

#include <vector>
#include <string>
#include <ostream>

class StringIntern {
	//static parts:
public:
	static std::vector<std::string> s_strings;
	static StringIntern Create(std::string fromString);

	StringIntern(std::string fromString);
private:
	static void AddString(std::string toAdd);
	static int const CreateInternal(std::string fromString);

	//non-static parts:
public:
	bool operator==(StringIntern& rhs) const;
	//operator char const* const() const;
	operator char const*() const;
	char const * const toString() const;

private:
	int const idx;
	explicit StringIntern(int idx);

	//need << overload to work
	friend std::ostream& operator<<(std::ostream&, StringIntern&);
};

StringIntern operator"" _i(char const* in);
std::ostream& operator<< (std::ostream& os, StringIntern& si);
