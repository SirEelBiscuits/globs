#pragma once

#include <string>

void ReadFile(char const* file, std::string& buffer);

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

#define MAKE_INDEX(foo) template<> struct enumeration_traits<foo>: enumeration_trait_indexing{}
#define AS_INDEX(foo) static_cast<typename std::underlying_type<decltype(foo)>::type>(foo)
