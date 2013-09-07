#include "glwrapper.h"

void logGLErrors(char const* file, int line) {
	static StringIntern lc("GL ERROR");

	GLuint err;
	while((err = glGetError()) != GL_NO_ERROR) {
		if(file != nullptr && line != 0)
			Logger::log(lc.toString(), "%s:%d - %d: %s",
			       	file, line, err, gluErrorString(err)
			);
	}
}

void GL::Init(int screenWidth, int screenHeight, ScreenMode screenMode) {
	if(!glfwInit()) {
		Logger::log("ERR", "glfwInit failed");
		exit(EXIT_FAILURE);
	}
	Logger::log("INFO", "Initialising window (%d, %d)"
		, screenWidth, screenHeight);

	// TODO improve this
	int mode = GLFW_WINDOW;
	switch(screenMode) {
	case ScreenMode::Fullscreen:
		mode = GLFW_FULLSCREEN;
		break;
	case ScreenMode::Windowed:
		mode = GLFW_WINDOW;
		break;
	default:
		Logger::log("ERR", "Nonsensical mode requested");
		break;
	}
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);

	if(!glfwOpenWindow(
			screenWidth,
			screenHeight,
			8, 8, 8,
			0, 0, 0,
			mode
		)
	) {
		glfwTerminate();
		Logger::log("ERR", "Failed to open window");
		exit(EXIT_FAILURE);
	}
	Logger::log("INFO", "GL version: %s", glGetString(GL_VERSION));
	LOG_GL_ERRORS;

	Logger::log("INFO", "Starting GLEW");
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK) {
		glfwTerminate();
		Logger::log("ERR", "Failed to start GLEW");
		exit(EXIT_FAILURE);
	}
	Logger::log("INFO", "GLEW version: %s", glewGetString(GLEW_VERSION));
	LOG_GL_ERRORS;
	Logger::log("INFO", "Initialisation Complete");
}
