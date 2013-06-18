#include <string>

/*
 * @brief Load shader in a shader
 * @param file The source file.
 * @param shaderType Indicates the type of shader
 * @return The shader handle.
 */
GLuint LoadShader(char const* file, GLenum shaderType);

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
