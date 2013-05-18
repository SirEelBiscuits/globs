#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glfw.h>

#include "shader.h"

#include <iostream>
#include <string>
#include <fstream>

#include <cstdlib>


void ReadFile( char const* file, std::string& buffer) {
	std::ifstream f(file);

	char c = f.get();
	while( f.good() ) {
		buffer.push_back(c);
		c = f.get();
	}
	return;
}

GLuint LoadShaderFromBuffer(std::string const& buffer, GLenum shaderType) {
	char const* src = buffer.c_str();

	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	GLint test;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &test);
	if(!test) {
		std::cerr << "Shader compilation failed." << std::endl;
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		std::string log;
		log.reserve(length);
		glGetShaderInfoLog(shader, log.size(), nullptr, const_cast<char*>(log.data()));
		std::cerr << log << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	return shader;
}

GLuint LoadShader(char const* file, GLenum shaderType) {
	std::string buffer;
	ReadFile(file, buffer);
	return LoadShaderFromBuffer(buffer, shaderType);
}

GLuint CreateProgramFromShaders( GLuint vertShader, GLuint fragShader ) {
	GLuint prog = glCreateProgram();
	glAttachShader(prog, vertShader);
	glAttachShader(prog, fragShader);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	glLinkProgram(prog);
	glUseProgram(prog);

	return prog;
}

GLuint CreateProgram( char const* vertFile, char const* fragFile) {
	GLuint vertShader = LoadShader(vertFile, GL_VERTEX_SHADER);
	GLuint fragShader = LoadShader(fragFile, GL_FRAGMENT_SHADER);
	return CreateProgramFromShaders(vertShader, fragShader);
}

std::string frag(
R"(#version 150

in vec4 color_from_vshader;
out vec4 out_color;

void main() {
	out_color = color_from_vshader;
})"
);

std::string vert(
R"(#version 150

in vec4 position;
in vec4 color;
out vec4 color_from_vshader;

void main() {
	gl_Position = position;
	color_from_vshader = color;
})"
);


GLuint GetBasicShader() {
	std::cerr << frag << std::endl;
	std::cerr << vert << std::endl;

	GLuint VS = LoadShaderFromBuffer(vert, GL_VERTEX_SHADER);
	GLuint FS = LoadShaderFromBuffer(frag, GL_FRAGMENT_SHADER);
	return CreateProgramFromShaders(VS, FS);
}
