#pragma once

#include "../util/stringintern.h"
#include "../util/utility.h"

enum class TextureType {
	Diffuse,
	Normal,
	Count
};
MAKE_INDEX(TextureType);
/*
 * This is a base class to contain the shared interface for textures.
 *  I can't imagine it needing much adding to it.
 *
 *  Times added to: 2
 */
class Texture {
public:
	virtual ~Texture(){}
	virtual void cleanup() = 0;
	virtual void set() const = 0;
	virtual unsigned int getWidth() const = 0;
	virtual unsigned int getHeight() const = 0;
	virtual TextureType  getType() const = 0;

	static StringIntern StringFromTextureType(TextureType tt);
};

