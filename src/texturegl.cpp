#include "texturegl.h"
#include "shader.h"
#include "log.h"

TextureGL::TextureGL(GLuint handle)
	: handle(handle)
{}

void TextureGL::cleanup() {
	glDeleteTextures(1, &handle);
}

void TextureGL::set() const {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, handle);
	int texLocation = glGetUniformLocation(GetBasicShader(), "texture_sampler");
	glUniform1i(texLocation, 0);
	LOG_GL_ERRORS;
}
