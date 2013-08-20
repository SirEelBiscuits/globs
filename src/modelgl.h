#pragma once

#include "glwrapper.h"
#include "model.h"

class ModelGL : public Model {
private:
	GLuint vao;
	GLuint vertData;
	GLuint indexData;
	int    numIndices;

public:
	ModelGL(GLuint vao, GLuint vertData, GLuint indexData, int numIndices);
	//overrides
	virtual void Draw() const override;
	virtual void Cleanup()    override;
};

