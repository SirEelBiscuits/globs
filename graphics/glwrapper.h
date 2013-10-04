#pragma once

/**
 * \file Wraps openGL and related inclusions.
 *
 * This ensures they are always included in the correct order, and any
 * defines required by the project are set.
 *
 */

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glfw.h>

#include "../util/stringintern.h"
#include "../util/log.h"

/**
 * Dump all openGL errors via logger, on the "GL ERROR" channel.
 *
 * \sa Logger
 */
#define LOG_GL_ERRORS logGLErrors(__FILE__, __LINE__)
/**
 * Clear all openGL errors, without logging information about them
 */
#define CLEAR_GL_ERRORS while(glGetError() != GL_NO_ERROR);
/**
 * Defines valid screen modes for the project
 *
 * \todo Put in GL?
 */
enum class ScreenMode {
	Fullscreen,
	Windowed
};
/**
 * \sa LOG_GL_ERRORS
 * \todo move to GL class
 */
bool logGLErrors(char const* file, int line);

/**
 * Contains main openGL functions.
 *
 * This is a class rather than a namespace in case it gains state
 */
class GL {
public:
	/**
	 * Initialise the screen
	 *
	 * Attempts the closest screen mode it can, shouldn't fail if openGL
	 * is supported.
	 *
	 * \param screenWidth in pixels.
	 * \param screenHeight in pixels.
	 *
	 */
	static void Init(
		int screenWidth,
		int screenHeight,
		ScreenMode screenMode
	);
};
