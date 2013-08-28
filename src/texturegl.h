#pragma once

#include "texture.h"
#include "glwrapper.h"

class TextureGL : public Texture {
public:
	virtual void cleanup() override;
	virtual void set() const override;

	TextureGL(GLuint handle);
private:
	GLuint const handle;
	GLuint const textureUnitToUse;
};
