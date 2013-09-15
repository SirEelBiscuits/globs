#pragma once

#include "texture.h"
#include "glwrapper.h"

/*
 * OpenGL 3.x specific texture class.
 *
 * This class should work with pretty much any openGL version. GL keeps its
 *  data internally, so this class only holds handles, which can be used to
 *  manipulate GL data via its functions.
 */
class TextureGL : public Texture {
public:
	virtual ~TextureGL() override {}
	virtual void cleanup() override;
	virtual void set() const override;
	virtual unsigned int getWidth() const override;
	virtual unsigned int getHeight() const override;

	TextureGL(GLuint handle);
private:
	GLuint const handle;
	GLuint const textureUnitToUse;
};
