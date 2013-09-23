#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glfw.h>

#include "../util/stringintern.h"
#include "../util/log.h"

#define LOG_GL_ERRORS logGLErrors(__FILE__, __LINE__)
#define CLEAR_GL_ERRORS while(glGetError() != GL_NO_ERROR);
enum class ScreenMode {
	Fullscreen,
	Windowed
};
bool logGLErrors(char const* file, int line);

//TODO this should be made into a proper stand-alone object!
class GL {
public:
	static void Init(
		int screenWidth,
		int screenHeight,
		ScreenMode screenMode
	);
};
