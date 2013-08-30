#pragma once

#include <string>

/*
 * TODO: This needs a heavy rewrite to turn shaders into a properly
 * encapsulated class for general consumption.
 */

/*
 * @brief Load shader in a shader
 * @param file The source file.
 * @param shaderType Indicates the type of shader
 * @return The shader handle.
 */
GLuint LoadShader(char const* file, GLenum shaderType);

/*
 * @brief Load a shader from an in-memory buffer
 * @param buffer is the string containing the data
 * @param shaderType indicates the type of shader
 * @return The shader handle
 */
GLuint LoadShaderFromBuffer(std::string const& buffer, GLenum shaderType);

/*
 * @brief Create a shader program from the supplied files
 * @param vertFile Vertex shader source file.
 * @param fragFile Fragment shader source file.
 * @return The shader program handle.
 */
GLuint CreateProgram( char const* vertFile, char const* fragFile);

/*
 * @brief Get a basic shader which forwards colour and verts
 * @param force Use this parameter if you have deleted the returned
 * shader program and wish to have the program recreate it.
 * @return The ID of that shader.
 */
GLuint GetBasicShader(bool force = false);


/*
 * Binds the parameter name in program to the data specified
 */
GLuint BindParameter(
	GLuint program,
       	char const* name,
       	GLuint size,
       	GLenum type,
       	GLsizei stride,
	GLvoid* offset
);

/*
 * sets up a single texture sampler
 */
void BindTextureSampler(
	GLuint program,
       	char const* samplerName,
       	GLuint textureUnit
);

