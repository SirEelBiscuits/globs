#pragma once

#include "../util/stringintern.h"
#include "../util/utility.h"

/**
 * Types of a texture that might be used.
 *
 * The code will assign a texture slot per type, so that a shader may support
 * all of them symultaneously. Note that these also have string namesa
 * associated with them, which can be found in texture.cpp
 *
 * \sa texture.cpp
 */
enum class TextureType {
	Diffuse,
	Normal,
	Count
};
MAKE_INDEX(TextureType);

/**
 * This is a base class to contain the shared interface for textures.
 *
 * The interface is fairly minimal, containing onyl the methods needed to
 * use the texture, and ensure it has been loaded correctly.
 * I can't imagine it needing much adding to it.
 *
 * Times added to: 2
 */
class Texture {
public:
	/**
	 * virtual destructor in case it is required by derived classes
	 */
	virtual ~Texture(){}

	/**
	 * Call to clean up all owned resources.
	 */
	virtual void cleanup() = 0;

	/**
	 * Sets this texture to be used in its associated slot.
	 */
	virtual void set() const = 0;

	/**
	 * \returns the width of the associated texture, in pixels.
	 */
	virtual unsigned int getWidth() const = 0;

	/**
	 * \returns the height of the associated texture, in pixels.
	 */
	virtual unsigned int getHeight() const = 0;

	/**
	 * \returns which type of texture this is.
	 * \sa TextureType
	 */
	virtual TextureType  getType() const = 0;

	/**
	 * \returns a string intern with the name samplers this texture type
	 * 	is linked to should be given. See implementation for actual
	 * 	values.
	 */
	static StringIntern StringFromTextureType(TextureType tt);
};

