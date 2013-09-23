#include "glwrapper.h"
#include "textureloader.h"
#include "texturegl.h"
#include "glm.h"
#include "../util/log.h"
#include "../util/stringintern.h"

Texture* TextureLoader::LoadTexture(IImageLoader&& il, TextureType type) {
	CLEAR_GL_ERRORS
	static StringIntern const log("Texture");

	LOG_MSG(log.toString(), "generating GL texture");
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	LOG_GL_ERRORS;

	unsigned int w,h;
	w = il.getWidth();
	h = il.getHeight();
	void* data = il.getDataPointer();
	if(data == nullptr) {
		LOG_MSG("ERROR", "Image loader gave null pointer");
		return nullptr;
	}

	LOG_MSG(log.toString(), "file loaded, size (%d, %d)", w, h);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	LOG_MSG(log.toString(), "uploading data..");
	glTexImage2D(
		GL_TEXTURE_2D,
	       	0,
	       	GL_RGBA,
	       	w,
	       	h,
	       	0,
	       	GL_RGBA,
	       	GL_UNSIGNED_BYTE,
	       	data
	);
	LOG_GL_ERRORS;

	LOG_MSG(log.toString(), "Texture load finished GL id: %d", tex);
	return new TextureGL(tex, type);
}

