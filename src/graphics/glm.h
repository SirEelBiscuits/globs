#pragma once
#define GLM_FORCE_CXX11

#pragma GCC diagnostic push
// glm is full of dodgy code that generates warnings. I can't fix this,
//  so I'm suppressing the spew
#pragma GCC diagnostic ignored "-Wpedantic"
#include <glm.hpp>

#pragma GCC diagnostic pop
