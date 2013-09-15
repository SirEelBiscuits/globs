#pragma once

#include <vector>
#include <string>
#include <ostream>

/*
 * String Intern
 *
 * String intern is an object for storing strings which are used commonly
 * through a codebase, without wasting lots of memory. Creating a string can
 * be slow, but long term it should be beneficial to have done so.
 *
 * USAGE:
 * create a string:
 * auto foo = StringIntern::Create("Some string");
 * - or -
 * StringIntern foo("some string");
 *
 * To use as a string:
 * foo.toString();
 * There is also an implicit conversion to char const*
 * TODO: implicit convert to std::string?
 *
 * TODO: pre-set strings list?
 * 	this would allow for data to be baked and a string set created,
 * 	which would shortcut initialising those strings :)
 */
class StringIntern {
	//static parts:
public:
	static std::vector<std::string> s_strings;
	static StringIntern Create(std::string fromString);

private:
	static void AddString(std::string toAdd);
	static int const CreateInternal(std::string fromString);

	//non-static parts:
public:
	StringIntern(std::string fromString);

	bool operator==(StringIntern& rhs) const;
	operator char const*() const;
	char const * const toString() const;

private:
	int const idx;
	explicit StringIntern(int idx);
};

StringIntern operator"" _i(char const* in);
std::ostream& operator<< (std::ostream& os, StringIntern& si);
