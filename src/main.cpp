#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glfw.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

#include "main.h"
#include "shader.h"
#include "version.inc"
#include "arrays.h"
#include "log.h"
#include "modelloader.h"
#include "model.h"

#include <IL/il.h>

int main(int argc, char* argv[]) {
	Init(argc, argv);

	Model* test;

	char const* modelsource = "pinwheel.obj";
	test = LoadModelFromFile(modelsource);
	test->list();

	std::vector<GLfloat> verts = {
		0.,	0.,
		.5,	0.,
		.5,	.5,

		0.,	0.,
		0.,	.5,
		-.5,	.5,

		0.,	0.,
		-.5,	0.,
		-.5,	-.5,

		0.,	0.,
		0.,	-.5,
		.5,	-.5
	};

	std::vector<GLfloat> colors = {
		1.0,	1.0,	1.0,
		1.0,	1.0,	0.3,
		1.0,	1.0,	1.0,
		1.0,	1.0,	1.0,
		1.0,	1.0,	1.0,
		1.0,	1.0,	1.0,
		1.0,	1.0,	1.0,
		1.0,	0.3,	1.0,
		1.0,	1.0,	1.0,
		1.0,	1.0,	1.0,
		1.0,	1.0,	1.0,
		0.5,	1.0,	1.0
	};

	std::vector<GLfloat> interleaved;

	Interleave(verts, 2, colors, 3, interleaved);

	GLuint vbo; glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, interleaved.size() * sizeof(GLfloat) , interleaved.data(), GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	BindParameter(GetBasicShader(), "position", 2, GL_FLOAT, 5 * sizeof(GLfloat), 0);
	BindParameter(GetBasicShader(), "color", 3, GL_FLOAT, 5 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat)*2));

	glClearColor(1.,0.,0.,1.);
	while(glfwGetWindowParam(GLFW_OPENED)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 12);

		glfwSwapBuffers();

		//temporary shutdown command
		if(glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
			break;
	}
	glfwTerminate();
	return 0;
}

void Init(int argc, char* argv[]) {
	Gargamel::Process(Arguments, argc, argv);

	if(Gargamel::ArgumentSet[Help].isArgumentPresent) {
		Gargamel::ShowUsage();
		exit(EXIT_SUCCESS);
	}

	Logger::setLogAll(Gargamel::ArgumentSet[LogAll].isArgumentPresent);
	Logger::echo(Gargamel::ArgumentSet[EchoLog].isArgumentPresent);
	//Technically this should go two lines earlier, but there is no way for it to
	// fail before here, and no way for that output to go anywhere either
	Logger::log("INFO", "Initialising logger");
	if(Gargamel::ArgumentSet[LogFile].isArgumentPresent) {
		if(!Logger::setFileName(Gargamel::ArgumentSet[LogFile].argumentValue)) {
			Logger::log("ERR", "Failed to open log file");
		}
	}
	for(auto s : *(Gargamel::ArgumentSet[LogChannel].argumentArray)) {
		Logger::activateChannel(s);
	}

	Logger::log("INFO", "Starting version " VERSION);
	if(!glfwInit()) {
		Logger::log("ERR", "glfwInit failed");
		exit(EXIT_FAILURE);
	}

	Logger::log("INFO", "Initialising window");
	int w = Gargamel::ArgumentSet[ScreenWidth].intVal();
	int h = Gargamel::ArgumentSet[ScreenHeight].intVal();
	int mode = GLFW_WINDOW;
	if(Gargamel::ArgumentSet[FullScreen].isArgumentPresent)
		mode = GLFW_FULLSCREEN;
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);

	if(!glfwOpenWindow(w, h, 8, 8, 8, 0, 0, 0, mode)) {
		glfwTerminate();
		Logger::log("ERR", "Failed to open window");
		exit(EXIT_FAILURE);
	}

	Logger::log("INFO", "Starting GLEW");
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK) {
		glfwTerminate();
		Logger::log("ERR", "Failed to start GLEW");
		exit(EXIT_FAILURE);
	}

	Logger::log("INFO", "Starting devIL");
	ilInit();

	Logger::log("INFO", "Initialisation Complete");
}
