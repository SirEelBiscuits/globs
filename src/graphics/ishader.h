#pragma once

#include "vert.h"
#include "texture.h"

/**
 * Shader interface class
 *
 * Defines the functions shaders need to support for this project to use
 * them.
 */
class IShader {
public:
	/**
	 * virtual destructor, in case its needed by deriving classes.
	 */
	virtual ~IShader(){}

	/**
	 * \returns a uniquely identifying number.
	 */
	virtual unsigned int getShaderID() const = 0;

	/**
	 * Check if a shader uses this texture type.
	 *
	 * Note that how that texture is used is dependent on the actual
	 * shader.
	 */
	virtual bool isTextureTypeSupported(TextureType type) const = 0;

	/**
	 * Check if a shader uses this VertComponent
	 *
	 * Note that how that attribute is used is dependent on the actual
	 * shader.
	 */
	virtual bool isAttributeSupported(VertComponent attribute) const = 0;

	/**
	 * Set this shader as the shader to use currently.
	 *
	 * Objects drawn after this call will use this shader.
	 */
	virtual bool set() const = 0;

	/**
	 * Binds the shaders parameters to the data input.
	 *
	 * The way this works may be openGL specific
	 */
	virtual bool bind() const = 0;

	/**
	 * Check shaders validity.
	 *
	 * Any and all library methods to check this should be used.
	 */
	virtual bool isShaderValid() const = 0;
};

