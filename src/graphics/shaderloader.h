#pragma once

#include "ishader.h"
#include "shadergl.h"

#include "../util/utility.h"
#include "../util/stringintern.h"

#include <string>

/**
 * Factory class for shader objects.
 *
 * This currently only returns ShaderGL objects.
 */
class ShaderLoader {
public:
	/**
	 * Opens a file, reads it in and passes it to the other overload
	 *
	 * Don't repeat yourself :)
	 */
	static IShader* LoadShaderFromFiles(
		char const* fragmentShaderFilename,
		char const* vertexShaderFilename
	);

	/**
	 * Creates a shader program from vertex and fragment shaders.
	 *
	 * This will automatically detect the supported vertex attributes
	 * and supported texture types from the shader's arguments. To see
	 * which names are picked up for which variables, see the appropriate
	 * documentation.
	 *
	 * \returns nullptr on failure
	 * \sa VertComponent
	 * \sa TextureType
	 */
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
