#pragma once

#include "ishader.h"
#include "texture.h"
#include "vert.h"

#include "../util/utility.h"
#include "glwrapper.h"

class ShaderGL : public IShader {
public:
	ShaderGL(GLuint id);
	ShaderGL(
		GLuint id,
		std::vector<VertComponent>& attributeTypes,
	       	std::vector<TextureType>& textureTypes
	);
	virtual ~ShaderGL();
	virtual unsigned int getShaderID() const override;
	virtual bool isTextureTypeSupported(TextureType type) const override;
	virtual bool isAttributeSupported(VertComponent attribute) const override;
	virtual bool set() const override;
	virtual bool bind() const override;
	virtual bool isShaderValid() const override;
private:
	GLuint shaderID;
	bool supportedTextureTypes[AS_INDEX(TextureType::Count)];
	bool supportedAttributes[AS_INDEX(VertComponent::Count)];
};

