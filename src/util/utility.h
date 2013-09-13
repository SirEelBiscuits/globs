#pragma once

#include <string>

/*
 * Reads a file into a std::string, no streaming or any of that nonsense.
 */
void ReadFile(char const* file, std::string& buffer);

/*
 * C++11 adds enum class, which is a more typesafe form of C's enum. Sadly
 * this type can't be used for array sizing or indexing as is, so some magic
 * needs to be done to get this to work.
 *
 * USAGE:
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

template<typename e>
constexpr
typename std::enable_if<enumeration_traits<e>::does_index,
	 typename std::underlying_type<e>::type>::type
operator+(e val) {
	return static_cast<typename std::underlying_type<e>::type>(val);
}

template<typename e>
typename std::enable_if<enumeration_traits<e>::does_index,
	 e& >::type
operator++(e& val) {
	return val = static_cast<e>(+val + 1);
}

#define MAKE_INDEX(foo) template<>\
       	struct enumeration_traits<foo>: enumeration_trait_indexing{}
#define AS_INDEX(foo) static_cast<typename \
       	std::underlying_type<decltype(foo)>::type>(foo)
