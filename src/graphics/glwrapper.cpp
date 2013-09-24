#include "glwrapper.h"

bool logGLErrors(char const* file, int line) {
	static StringIntern lc("GL ERROR");
	bool retVal = true;

	GLuint err;
	while((err = glGetError()) != GL_NO_ERROR) {
		retVal = false;
		if(file != nullptr && line != 0)
			LOG_MSG_LOC(lc.toString(), file, line, "%d: %s",
			       	err, gluErrorString(err)
			);
	}
	return retVal;
}

void GL::Init(int screenWidth, int screenHeight, ScreenMode screenMode) {
	if(!glfwInit()) {
		LOG_MSG("ERR", "glfwInit failed");
		exit(EXIT_FAILURE);
	}
	LOG_MSG("INFO", "Initialising window (%d, %d)"
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
		LOG_MSG("ERR", "Nonsensical mode requested");
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
		LOG_MSG("ERR", "Failed to open window");
		exit(EXIT_FAILURE);
	}
	LOG_MSG("INFO", "GL version: %s", glGetString(GL_VERSION));
	LOG_GL_ERRORS;

	LOG_MSG("INFO", "Starting GLEW");
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK) {
		glfwTerminate();
		LOG_MSG("ERR", "Failed to start GLEW");
		exit(EXIT_FAILURE);
	}
	LOG_MSG("INFO", "GLEW version: %s", glewGetString(GLEW_VERSION));
	LOG_GL_ERRORS;
	LOG_MSG("INFO", "Initialisation Complete");
}
