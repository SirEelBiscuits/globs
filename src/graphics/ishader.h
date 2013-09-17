#pragma once

#include "vert.h"
#include "texture.h"

class IShader {
public:
	virtual ~IShader(){}
	virtual unsigned int getShaderID() const = 0;
	virtual unsigned int getTextureSlot(TextureType type) const = 0;
	virtual unsigned int getNumTextureSlots() const = 0;
	virtual bool isTextureTypeSupported(TextureType type) const = 0;
	virtual bool isAttributeSupported(VertComponent attribute) const = 0;
};

