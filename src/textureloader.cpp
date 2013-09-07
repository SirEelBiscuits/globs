#include "glwrapper.h"
#include "textureloader.h"
#include "texturegl.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include "log.h"
#include "stringintern.h"
#include "glm.h"

#include "glm.h"

Texture* TextureLoader::LoadTextureFromFile(char const* fileName) {
	CLEAR_GL_ERRORS
	static StringIntern const log("Texture");

	LOG_MSG(log.toString(), "Starting texture load (%s)", fileName);
	static bool initialised = false;
	if(!initialised) {
		LOG_MSG(log.toString(), "Initialising devIL");
		ilInit();
		iluInit();
		initialised = true;
	}

	ilBindImage(1);
	LOG_MSG(log.toString(), "Loading image..");
	if(!ilLoadImage(fileName)) {
		LOG_MSG("ERROR", "image load failed");
		return nullptr;
	}
	if(ilGetInteger(IL_IMAGE_FORMAT) != IL_RGBA) {
		LOG_MSG(log.toString(), "enforcing format rules..");
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	}
	ILinfo imgInfo;
	iluGetImageInfo(&imgInfo);
	if(imgInfo.Origin == IL_ORIGIN_UPPER_LEFT) {
		LOG_MSG(log.toString(), "Flipping image");
		iluFlipImage();
	}
	LOG_MSG(log.toString(), "complete");

	LOG_MSG(log.toString(), "generating GL texture");
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	LOG_GL_ERRORS;

	ILuint w,h;
	w = ilGetInteger(IL_IMAGE_WIDTH);
	h = ilGetInteger(IL_IMAGE_HEIGHT);
	ILubyte* data = ilGetData();
	ILenum err;
	while((err = ilGetError())) {
		LOG_MSG("ERROR", "DevIL error: %d", err);
	}
	if(data == nullptr)
		LOG_MSG("ERROR", "DevIL gave null pointer");
	LOG_MSG(log.toString(), "file loaded, size (%d, %d)", w, h);
	LOG_MSG(log.toString(), "data size: %d",
		       	ilGetInteger(IL_IMAGE_SIZE_OF_DATA));
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
	return new TextureGL(tex);
}

