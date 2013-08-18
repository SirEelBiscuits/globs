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
	virtual void list() const override;
	virtual void Draw() const override;
	virtual void Cleanup()    override;

	// new methods
	Vert     getOrCreateVert(unsigned int Index);
	Vert     getVert(unsigned int Index) const;
	void     setVert(unsigned int Index, Vert newValue);
	int      getIndex(unsigned int Index) const;
	void     setIndex(unsigned int Index, uint16_t newValue);
	void     appendIndex(uint16_t newIndex);

	//Once this function is called, any action which will change the size of
	// the contained arrays will fail, as these can potentially move the data
	// in memory which can be catastrophic to OpenGL!
	//
	// TODO:: Does all this const shit even need  doing? I think we can just
	// free the data once it is finalised for a static model
	//
	//Changing the contents of the arrays is still ok though
	void FinaliseLoad();

private:
	bool                   _const = false;
	std::vector<Vert>      _verts;
	std::vector<int>       _indices;

	bool isConst();
};

