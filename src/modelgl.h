#pragma once

#include "glwrapper.h"
#include "model.h"

class ModelGL : public Model {
private:
	GLuint vbo;
	GLuint vao;

public:
	virtual void     list() const override;
	Vert     getOrCreateVert(unsigned int Index);
	Vert     getVert(unsigned int Index) const;
	void     setVert(unsigned int Index, Vert newValue);
	uint16_t getIndex(unsigned int Index) const;
	void     setIndex(unsigned int Index, uint16_t newValue);
	void     appendIndex(uint16_t newIndex);

	//Once this function is called, any action which will change the size of
	// the contained arrays will fail, as these can potentially move the data
	// in memory which can be catastrophic to OpenGL!
	//
	//Changing the contents of the arrays is still ok though
	void FinaliseLoad();
	virtual void Draw() const override;
	virtual void Cleanup() override;

private:
	bool                   _const = false;
	std::vector<Vert>      _verts;
	std::vector<uint16_t>  _indices;

	bool isConst();
};

