#pragma once

#include "ishader.h"
#include "texture.h"
#include "vert.h"

#include "../util/utility.h"
#include "glwrapper.h"

class ShaderGL : public IShader {
public:
	//TODO: initialiser list for tex/attributes enabled?
	ShaderGL(GLuint id);
	virtual ~ShaderGL();
	virtual unsigned int getShaderID() const override;
	virtual bool isTextureTypeSupported(TextureType type) const override;
	virtual bool isAttributeSupported(VertComponent attribute) const override;
	virtual bool bind() const;
private:
	GLuint shaderID;
	bool supportedTextureTypes[AS_INDEX(TextureType::Count)];
	bool supportedAttributes[AS_INDEX(VertComponent::Count)];
};

