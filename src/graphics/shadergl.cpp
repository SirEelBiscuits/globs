#include "shadergl.h"

ShaderGL::ShaderGL(GLuint id)
	: shaderID(id)
	, supportedTextureTypes{}
	, supportedAttributes{}
{
}

ShaderGL::~ShaderGL(){}

unsigned int ShaderGL::getShaderID() const {
	return shaderID;
}

bool ShaderGL::isTextureTypeSupported(TextureType type) const {
	return supportedTextureTypes[AS_INDEX(type)];
}

bool ShaderGL::isAttributeSupported(VertComponent attribute) const {
	return supportedAttributes[AS_INDEX(attribute)];
}

bool ShaderGL::bind() const {
	//TODO
	return false;
}
