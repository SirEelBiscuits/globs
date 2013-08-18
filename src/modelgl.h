#pragma once

#include "glwrapper.h"
#include "model.h"

class ModelGL : public Model {
private:
	GLuint vertData;
	GLuint indexData;
	GLuint vao;
	int    numVerts;

public:
	//overrides
	virtual void Draw() const override;
	virtual void Cleanup()    override;

	// new methods
	Vert     getOrCreateVert(unsigned int Index);
	Vert     getVert(unsigned int Index) const;
	void     setVert(unsigned int Index, Vert newValue);
	int      getIndex(unsigned int Index) const;
	void     setIndex(unsigned int Index, uint16_t newValue);
	void     appendIndex(uint16_t newIndex);

	//This will put all the data in the vectors into openGL's memory,
	// and clear the arrays here
	//
	//TODO separate objects for pre and post FinaliseLoad?
	void FinaliseLoad();

private:
	std::vector<Vert>      _verts;
	std::vector<int>       _indices;
};

