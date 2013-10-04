#include "texturegl.h"
#include "../util/log.h"

TextureGL::TextureGL(GLuint handle, TextureType type)
	: handle(handle)
	, type(type)
{}

void TextureGL::cleanup() {
	LOG_MSG("Texture", "Cleaning up texture %u", handle);
	glDeleteTextures(1, &handle);
	LOG_GL_ERRORS;
}

void TextureGL::set() const {
	glActiveTexture(GL_TEXTURE0 + AS_INDEX(type));
	glBindTexture(GL_TEXTURE_2D, handle);
	LOG_GL_ERRORS;
}

unsigned int TextureGL::getWidth() const {
	glBindTexture(GL_TEXTURE_2D, handle);
	int val;
	glGetTexLevelParameteriv(
		GL_TEXTURE_2D,
	       	0,
	       	GL_TEXTURE_WIDTH,
	       	&val
	);
	return val;
}

unsigned int TextureGL::getHeight() const {
	glBindTexture(GL_TEXTURE_2D, handle);
	int val;
	glGetTexLevelParameteriv(
		GL_TEXTURE_2D,
	       	0,
	       	GL_TEXTURE_HEIGHT,
	       	&val
	);
	return val;
}

TextureType TextureGL::getType() const {
	return type;
}
