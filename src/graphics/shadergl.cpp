#include "shadergl.h"

ShaderGL::ShaderGL(GLuint id)
	: shaderID(id)
	, supportedTextureTypes{}
	, supportedAttributes{}
{
}

ShaderGL::ShaderGL(
	GLuint id,
	std::vector<VertComponent>& attributeTypes,
	std::vector<TextureType>& textureTypes
)
	: shaderID(id)
	, supportedTextureTypes{}
	, supportedAttributes{}
{
	for(auto t : textureTypes) {
		supportedTextureTypes[AS_INDEX(t)] = true;
	}
	for(auto a : attributeTypes) {
		supportedAttributes[AS_INDEX(a)] = true;
	}
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

bool ShaderGL::set() const {
	if(!isShaderValid())
		return false;
	glUseProgram(shaderID);
	LOG_GL_ERRORS;
	return true;
}

bool ShaderGL::bind() const {
	if(!isShaderValid())
		return false;
	for(int i = 0; i < AS_INDEX(VertComponent::Count); ++i ) {
		VertComponent cur = static_cast<VertComponent>(i);
		if(isAttributeSupported(cur)) {
			GLint pos = glGetAttribLocation(
				getShaderID(),
				Vert::StringFromVertComponent(cur)
					.toString()
			);
			glVertexAttribPointer(
				pos,
				Vert::getElementWidths(cur),
				GL_FLOAT,
				GL_FALSE,
				Vert::getStride(),
				reinterpret_cast<void*>(
					Vert::getOffset(cur)
				)
			);
		}
	}

	for(int i = 0; i < AS_INDEX(TextureType::Count); ++i) {
		TextureType cur = static_cast<TextureType>(i);
		if(isTextureTypeSupported(cur)) {
			glUniform1i(
				glGetUniformLocation(
					getShaderID(),
					Texture::StringFromTextureType(
						cur
					).toString()
				),
				AS_INDEX(cur)
			);
		}
	}
	return true;
}

bool ShaderGL::isShaderValid() const {
	if(!glIsProgram(shaderID))
		return false;
	glValidateProgram(shaderID);
	GLint retVal;
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &retVal);
	if(retVal == GL_TRUE)
		return true;
	int len;
        glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &len);
	std::string buffer(len+1, '\0');
	glGetProgramInfoLog(
		shaderID,
	       	len,
	       	nullptr,
	       	const_cast<char*>(buffer.data())
	);
	LOG_MSG("ERROR", "Shader validation results: %s", buffer.c_str());
	return false;
}
