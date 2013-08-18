#include "modelgl.h"
#include "vert.h"
#include "shader.h"

#include <iostream>

#define LOG "ModelGL"

void ModelGL::FinaliseLoad() {
	Logger::log(LOG, "Sending model data to GL");
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	Logger::log(LOG,"Allocating vertex store size: %d", sizeof(Vert) * _verts.size());
	glGenBuffers(1, &vertData);
	glBindBuffer(GL_ARRAY_BUFFER, vertData);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * _verts.size(), _verts.data(), GL_STATIC_DRAW);

	Logger::log(LOG,"Initialising shader params");

	for( auto vc : {
		VertComponent::Position,
	       	VertComponent::Colour,
	       	VertComponent::Texture,
	       	VertComponent::Normal
	} ) {
		BindParameter(
		   	GetBasicShader(),
			stringFromVertComponent(vc),
			Vert::getElementWidths(vc),
			GL_FLOAT,
			Vert::getStride(),
			(GLvoid*)Vert::getOffset(vc)
		);
	}

	Logger::log(LOG, "Initialising element array size: %d", sizeof(int) * _indices.size());
	glGenBuffers(1, &indexData);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexData);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * _indices.size(), _indices.data(), GL_STATIC_DRAW);

 	numVerts = _indices.size();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	Logger::log(LOG, "Freeing memory...");
	_verts.clear();
	_verts.shrink_to_fit();
	_indices.clear();
	_indices.shrink_to_fit();
	Logger::log(LOG, "all done");
}

void ModelGL::Draw() const {
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexData);
	glDrawElements(GL_TRIANGLES, numVerts, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ModelGL::Cleanup() {
	Logger::log(LOG, "Cleaning up model");
	glDeleteBuffers(1, &vertData);
	glDeleteBuffers(1, &indexData);
	glDeleteVertexArrays(1, &vao);
	Logger::log(LOG, "Done");
}

Vert ModelGL::getOrCreateVert(unsigned int Index) {
	if(Index >= _verts.size()) {
		_verts.resize(Index + 1);
		return _verts[Index];
	}
	return _verts[Index];
}

Vert ModelGL::getVert(unsigned int Index) const {
	return _verts[Index];
}

void ModelGL::setVert(unsigned int Index, Vert newValue) {
	_verts[Index] = newValue; //do your own damn bounds check
}

int ModelGL::getIndex(unsigned int Index) const {
	return _indices[Index];
}

void ModelGL::setIndex(unsigned int Index, uint16_t newValue) {
	_indices[Index] = newValue;
}

void ModelGL::appendIndex(uint16_t newIndex) {
	_indices.push_back(newIndex);
}

