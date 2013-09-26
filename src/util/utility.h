#pragma once

#include <string>

/**
 * Reads a file into a std::string
 *
 * This dumps the whole file into buffer, if its too big, that's your
 * problem.
 */
void ReadFile(char const* file, std::string& buffer);

/**
 * Trait to make an enum class usable as an integer
 *
 * C++11 adds enum class, which is a more typesafe form of C's enum. Sadly
 * this type can't be used for array sizing or indexing as is, so some magic
 * needs to be done to get this to work.
 *
 * \section Usage
 * enum class Bar {
 *     X,
 *     Y,
 *     Z
 * };
 * MAKE_INDEX(Bar);
 *
 * Bar's members can now be used as an index like so:
 *
 * int SomeArray[AS_INDEX(Bar::X)];
 *
 * Sadly there is no way to use Bar as a sizing value :(
 */
template<typename e>
struct enumeration_traits;

struct enumeration_trait_indexing {
	static constexpr bool does_index = true;
};

/**
 * Allow unary + be used to convert an enum class value into an int
 *
 * It's pretty ugly, but at least it's brief.
 */
template<typename e>
constexpr
typename std::enable_if<enumeration_traits<e>::does_index,
	 typename std::underlying_type<e>::type>::type
operator+(e val) {
	return static_cast<typename std::underlying_type<e>::type>(val);
}

/**
 * Allow ++ to be applied to an enum class
 *
 * Don't overflow it, or weird things can happen.
 */
template<typename e>
typename std::enable_if<enumeration_traits<e>::does_index,
	 e& >::type
operator++(e& val) {
	return val = static_cast<e>(+val + 1);
}

/**
 * use this on an enum after its declaration to enable the indexing trait.
 *
 * This allows the use of AS_INDEX on it, as well as incrementing variables
 * of that type.
 */
#define MAKE_INDEX(foo) template<>\
       	struct enumeration_traits<foo>: enumeration_trait_indexing{}
/**
 * Converts an enum class with the index trait to its underlying type.
 *
 * Use this to use an enum class value to index an array or similar.
 */
#define AS_INDEX(foo) static_cast<typename \
       	std::underlying_type<decltype(foo)>::type>(foo)
