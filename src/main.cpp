#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glfw.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>


#include "shader.h"
#include "version.inc"
#include "arrays.h"

#include <IL/il.h>

int main() {
	std::cout << "Starting version " VERSION << std::endl;
	if( !glfwInit() ) {
		std::cerr << "fail";
		exit(-1);
	}

	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);


	if( !glfwOpenWindow(800,600,8,8,8,0,0,0,GLFW_WINDOW) ) {
		glfwTerminate();
		std::cerr << "fail2";
		exit(-1);
	}

	glewExperimental = GL_TRUE;
	if( glewInit() != GLEW_OK) {
		glfwTerminate();
		exit(-1);
	}

	ilInit();

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

	GLuint vbo; glGenBuffers(1, &vbo);
	GLuint vbo2; glGenBuffers(1, &vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat) , verts.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat) , colors.data(), GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	BindParameter(GetBasicShader(), "position", 2, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	BindParameter(GetBasicShader(), "color", 3, GL_FLOAT, 0, 0);

	glClearColor(1.,0.,0.,1.);
	while(glfwGetWindowParam(GLFW_OPENED)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 12);

		glfwSwapBuffers();
	}
	glfwTerminate();
	return 0;
}