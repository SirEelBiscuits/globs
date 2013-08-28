#include "texturegl.h"
#include "shader.h"
#include "log.h"

TextureGL::TextureGL(GLuint handle)
	: handle(handle)
	, textureUnitToUse(0)
{}

void TextureGL::cleanup() {
	glDeleteTextures(1, &handle);
}

void TextureGL::set() const {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, handle);
	LOG_GL_ERRORS;
}
