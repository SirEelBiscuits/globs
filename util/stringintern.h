#pragma once

#include <vector>
#include <string>
#include <ostream>

/**
 * String Intern
 *
 * String intern is an object for storing strings which are used commonly
 * through a codebase, without wasting lots of memory. Creating a string can
 * be slow, but long term it should be beneficial to have done so.
 *
 * \section usage
 * create a string:
 * auto foo = StringIntern::Create("Some string");
 * - or -
 * StringIntern foo("some string");
 *
 * To use as a string:
 * foo.toString();
 * There is also an implicit conversion to char const*
 * \todo: implicit convert to std::string?
 *
 * \todo: pre-set strings list?
 * 	this would allow for data to be baked and a string set created,
 * 	which would shortcut initialising those strings :)
 */
class StringIntern {
public:
	/**
	 * Creates a string intern
	 *
	 * This will reuse the actual string from any identical
	 * stringintern, but is a slow operation. Use as little as possible.
	 */
	StringIntern(std::string fromString);

	/**
	 * Check equality with other string interns
	 *
	 * Note that this is a very fast operation.
	 */
	bool operator==(StringIntern& rhs) const;

	/**
	 * Implicit conversion to c-style string
	 */
	operator char const*() const;
	/**
	 * Explicit conversion to c-style string
	 */
	char const * const toString() const;

private:
	static void AddString(std::string toAdd);
	static int const CreateInternal(std::string fromString);

	int const idx;
	explicit StringIntern(int idx);
	static std::vector<std::string> s_strings;
};

/**
 * String literal
 *
 * Strings written like "foo"_i will be constructed as string interns.
 */
StringIntern operator"" _i(char const* in, size_t numChars);

/**
 * Easy output with c++ streams
 */
std::ostream& operator<< (std::ostream& os, StringIntern& si);
