#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glfw.h>

#include "shader.h"
#include "log.h"
#include "utility.h"

#include <iostream>
#include <string>
#include <fstream>

#include <cstdlib>

GLuint LoadShaderFromBuffer(std::string const& buffer, GLenum shaderType) {
	char const* src = buffer.c_str();

	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	GLint test;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &test);
	if(!test) {
		Logger::log("Shader", "Shader compilation failed.");
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		std::string log;
		log.reserve(length);
		glGetShaderInfoLog(shader, log.size(), nullptr, const_cast<char*>(log.data()));
		Logger::log("Shader", log);
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

GLuint CreateProgramFromShaders(GLuint vertShader, GLuint fragShader) {
	GLuint prog = glCreateProgram();
	glAttachShader(prog, vertShader);
	glAttachShader(prog, fragShader);

	glLinkProgram(prog);
	glUseProgram(prog);

	return prog;
}

GLuint CreateProgram(char const* vertFile, char const* fragFile) {
	GLuint vertShader = LoadShader(vertFile, GL_VERTEX_SHADER);
	GLuint fragShader = LoadShader(fragFile, GL_FRAGMENT_SHADER);
	auto prog = CreateProgramFromShaders(vertShader, fragShader);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	return prog;
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


GLuint GetBasicShader(bool force) {
	static GLuint BasicShader = -1;

	if(BasicShader != static_cast<GLuint>(-1) && !force)
		return BasicShader;

	Logger::log("Shader", frag);
	Logger::log("Shader", vert);

	GLuint VS = LoadShaderFromBuffer(vert, GL_VERTEX_SHADER);
	GLuint FS = LoadShaderFromBuffer(frag, GL_FRAGMENT_SHADER);
	return BasicShader = CreateProgramFromShaders(VS, FS);
}

GLuint BindParameter(
	GLuint program,
       	char const* name,
       	GLuint size,
       	GLenum type,
       	GLsizei stride,
	GLvoid* offset
) {
	GLint position = glGetAttribLocation(program, name);
	glVertexAttribPointer(position, size, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(position);
	return position;
}
