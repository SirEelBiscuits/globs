#include "glwrapper.h"

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
		Logger::log("Shader", "Log reads: %s", log.c_str());
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

in vec4 colour_from_vshader;
in vec2 texture_from_vshader;
out vec4 out_colour;

uniform sampler2D texture_sampler;

void main() {
	out_colour = texture(texture_sampler, texture_from_vshader);
})"
);

std::string vert(
R"(#version 150

in vec4 position;
in vec4 colour;
out vec4 colour_from_vshader;

in vec2 texture;
out vec2 texture_from_vshader;

void main() {
	gl_Position = position;
	colour_from_vshader = colour;
	texture_from_vshader = texture;
})"
);


GLuint GetBasicShader(bool force) {
	static GLuint BasicShader = -1;

	if(BasicShader != static_cast<GLuint>(-1) && !force)
		return BasicShader;

	Logger::log("Shader", "Loaded fragment shader: \n%s\nEOF\n", frag.c_str());
	Logger::log("Shader", "Loaded vertex shader: \n%s\nEOF\n", vert.c_str());

	GLuint VS = LoadShaderFromBuffer(vert, GL_VERTEX_SHADER);
	GLuint FS = LoadShaderFromBuffer(frag, GL_FRAGMENT_SHADER);

	BasicShader = CreateProgramFromShaders(VS, FS);
	LOG_GL_ERRORS;
	return BasicShader;
}

GLuint BindParameter(
	GLuint program,
       	char const* name,
       	GLuint size,
       	GLenum type,
       	GLsizei stride,
	GLvoid* offset
) {
	Logger::log("Shader", "Binding parameter '%s', size: %d, stride: %d, offset: %d", name, size, stride, offset);
	GLint position = glGetAttribLocation(program, name);
	glVertexAttribPointer(position, size, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(position);
	LOG_GL_ERRORS;
	return position;
}
