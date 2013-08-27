#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glfw.h>

#include "stringintern.h"
#include "log.h"

#define LOG_GL_ERRORS logGLErrors(__FILE__, __LINE__)
#define CLEAR_GL_ERRORS while(glGetError() != GL_NO_ERROR);
void logGLErrors(char const* file, int line);

