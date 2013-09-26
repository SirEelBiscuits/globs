#pragma once

#include "glwrapper.h"
#include "model.h"

/**
 * OpenGL 3.x specific model class
 *
 * Contains OpenGL data and functions, as necessary. OGL handles its data
 * internally for the most part, so this will just have a few handles which
 * can be used to manipulate the data through openGL functions.
 *
 * This class should be ok for OpenGL 4, but this is not tested.
 *
 * \sa Model
 */
class ModelGL : public Model {
public:
	/**
	 * \param vao ID for the Vertex Array Object
	 * \param vertData handle for the Buffer Object containing model data
	 * \param indexData handle for the Buffer Object containing the
	 * 	indices
	 * \param numIndices Number of elements in the index buffer
	 */
	ModelGL(
		GLuint vao,
	       	GLuint vertData,
	       	GLuint indexData,
	       	int numIndices
	);
	virtual ~ModelGL(){}

	//overrides

	virtual bool draw() const override;
	virtual bool cleanup()    override;
	virtual bool bind() const override;
	virtual bool unbind() const override;
	virtual bool useShader(Shader* shader) override;
	virtual unsigned int getID() const override;

private:
	GLuint vao;
	GLuint vertData;
	GLuint indexData;
	int    numIndices;
};

