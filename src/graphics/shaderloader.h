#pragma once

#include "ishader.h"
#include "shadergl.h"

#include "../util/utility.h"
#include "../util/stringintern.h"

#include <string>

class ShaderLoader {
public:
	static IShader* LoadShaderFromFiles(
		char const* fragmentShaderFilename,
		char const* vertexShaderFilename
	);
	static IShader* LoadShaderFromBuffers(
		std::string const& fragmentShader,
	       	std::string const& vertexShader
	);
private:
	static StringIntern LOG;
	static bool getShaderErrorLog(GLuint shader, GLenum ErrorToQuery);
	static GLuint LoadShaderFromBuffer(
		std::string const& buffer,
		GLenum shaderType
	);
	static GLuint CreateProgramFromShaders(
		GLuint fragShader,
		GLuint vertShader
	);
	static std::vector<TextureType> getSupportedTypes(
		GLuint program
	);
	static std::vector<VertComponent> getSupportedAttributes(
		GLuint program
	);
};
