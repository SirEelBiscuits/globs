#pragma once

#include "ishader.h"
#include "texture.h"
#include "vert.h"

#include "../util/utility.h"
#include "glwrapper.h"

/**
 * Implementation of Shader for openGL 3.x
 *
 * OpenGL handles shader programs as internal objects, so this really just
 * refers to the correct object, and forwards functions onto openGL.o
 *
 * \sa Shader
 */
class ShaderGL : public IShader {
public:
	/**
	 * Constructor
	 *
	 * The shader program with the given id should support the listed
	 * attribute and texture types. That is, there should be in
	 * variabels, and texture samplers with the names associated with
	 * those enum values.
	 *
	 * \param id The shader program to hold.
	 * \param attributeTypes supported attributes.
	 * \param textureTypes supported texture types
	 *
	 * \sa VertComponent
	 * \sa TextureType
	 */
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

	/**
	 * Bind the shader to a buffer object for use
	 *
	 * For this function to work, the Buffer Object that will use the
	 * shader must be bound. This will be called by ModelGL::useShader()
	 * internally, if this shader is passed to it.
	 *
	 * \sa ModelGL
	 */
	virtual bool bind() const override;
	virtual bool isShaderValid() const override;
private:
	GLuint shaderID;
	bool supportedTextureTypes[AS_INDEX(TextureType::Count)];
	bool supportedAttributes[AS_INDEX(VertComponent::Count)];
};

