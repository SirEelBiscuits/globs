
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

GLuint GetBasicShader();
