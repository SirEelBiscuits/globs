#include "glwrapper.h"

#include "textureloader.h"

#include "texturegl.h"
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

#include "log.h"

#include "stringintern.h"

#include "glm.h"

Texture* TextureLoader::LoadTextureFromFile(char const* fileName) {
	CLEAR_GL_ERRORS
	static StringIntern const log("Texture");

	Logger::log(log.toString(), "Starting texture load (%s)", fileName);
	static bool initialised = false;
	if(!initialised) {
		Logger::log(log.toString(), "Initialising devIL");
		ilInit();
		iluInit();
		initialised = true;
	}

	ilBindImage(1);
	Logger::log(log.toString(), "Loading image..");
	if(!ilLoadImage(fileName)) {
		Logger::log("ERROR", "image load failed");
		return nullptr;
	}
	if( ilGetInteger(IL_IMAGE_FORMAT) != IL_RGBA ) {
		Logger::log(log.toString(), "enforcing format rules..");
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	}

	ILinfo imgInfo;
	iluGetImageInfo(&imgInfo);
	if( imgInfo.Origin == IL_ORIGIN_UPPER_LEFT ) {
		Logger::log(log.toString(), "Flipping image");
		iluFlipImage();
	}

	Logger::log(log.toString(), "complete");

	Logger::log(log.toString(), "generating GL texture");
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
		Logger::log("ERROR", "DevIL error: %d", err);
	}
	if( data == nullptr )
		Logger::log("ERROR", "DevIL gave null pointer");
	Logger::log(log.toString(), "file loaded, size (%d, %d)", w, h);
	Logger::log(log.toString(), "data size: %d", ilGetInteger(IL_IMAGE_SIZE_OF_DATA));

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	Logger::log(log.toString(), "uploading data..");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	Logger::log(log.toString(), "Texture load finished GL id: %d", tex);
	return new TextureGL(tex);
}

