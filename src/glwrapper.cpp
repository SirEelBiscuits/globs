#include "glwrapper.h"

void logGLErrors(char const* file, int line) {
	static StringIntern lc("GL ERROR");

	GLuint err;
	while((err = glGetError()) != GL_NO_ERROR) {
		if( file != nullptr && line != 0 )
			Logger::log(lc.toString(), "%s:%d - %d: %s", file, line, err, gluErrorString(err));
	}
}

