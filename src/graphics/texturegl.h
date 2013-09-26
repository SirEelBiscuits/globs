#pragma once

#include "texture.h"
#include "glwrapper.h"

/**
 * OpenGL 3.x specific texture class.
 *
 * This class should work with pretty much any openGL version. GL keeps its
 *  data internally, so this class only holds handles, which can be used to
 *  manipulate GL data via its functions.
 *
 * \sa Texture
 */
class TextureGL : public Texture {
public:
	virtual ~TextureGL() override {}
	virtual void cleanup() override;
	virtual void set() const override;
	virtual unsigned int getWidth() const override;
	virtual unsigned int getHeight() const override;
	virtual TextureType  getType() const override;

	/**
	 * \param handle the id of the openGL texture object to use.
	 * \param type the type of the texture handle refers to
	 */
	TextureGL(GLuint handle, TextureType type);
private:
	GLuint const handle;
	TextureType type;
};
