#pragma once

#include "vert.h"
#include "texture.h"

class IShader {
public:
	virtual ~IShader(){}
	virtual unsigned int getShaderID() const = 0;
	virtual bool isTextureTypeSupported(TextureType type) const = 0;
	virtual bool isAttributeSupported(VertComponent attribute) const = 0;
	virtual bool set() const = 0;
	virtual bool isShaderValid() const = 0;

	//TODO Add function to bind supported things!
};

