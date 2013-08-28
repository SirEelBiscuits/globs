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
		ilutRenderer(ILUT_OPENGL);
		LOG_GL_ERRORS;
		initialised = true;
	}

	ilBindImage(1);
	Logger::log(log.toString(), "Loading image..");
	if(!ilLoadImage(fileName)) {
		Logger::log("ERROR", "image load failed");
		return nullptr;
	}
	Logger::log(log.toString(), "complete");

	Logger::log(log.toString(), "Setting up mipmaps (via devIL)");

	//TODO replace ilutGLBindTexImage it is not very portable
	GLuint tex = ilutGLBindTexImage();
	LOG_GL_ERRORS;
	ILenum Error;
	while((Error = ilGetError())) {
		Logger::log("ERROR", "DevIL error: %d", Error);
	}

	Logger::log(log.toString(), "Texture load finished GL id: %d", tex);
	return new TextureGL(tex);
}

