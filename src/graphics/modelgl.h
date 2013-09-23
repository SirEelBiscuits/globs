#pragma once

#include "glwrapper.h"
#include "model.h"

/*
 * OpenGL 3.x specific model class
 *
 * Contains OpenGL data and functions, as necessary. OGL handles its data
 *  internally for the most part, so this will just have a few handles which
 *  can be used to manipulate the data through openGL functions.
 *
 * This class should be ok for OpenGL 4, but this is not tested.
 */
class ModelGL : public Model {
private:
	GLuint vao;
	GLuint vertData;
	GLuint indexData;
	int    numIndices;

public:
	ModelGL(
		GLuint vao,
	       	GLuint vertData,
	       	GLuint indexData,
	       	int numIndices
	);

	//overrides

	virtual bool draw() const override;
	virtual void cleanup()    override;
	virtual unsigned int getID() const override;
};

