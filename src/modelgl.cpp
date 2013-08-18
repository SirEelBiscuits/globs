#include "modelgl.h"
#include "vert.h"
#include "shader.h"

#include <iostream>

void ModelGL::FinaliseLoad() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertData);
	glBindBuffer(GL_ARRAY_BUFFER, vertData);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * _verts.size(), _verts.data(), GL_STATIC_DRAW);

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

	glGenBuffers(1, &indexData);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexData);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * _indices.size(), _indices.data(), GL_STATIC_DRAW);

 	numVerts = _indices.size();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	_verts.clear();
	_verts.shrink_to_fit();
	_indices.clear();
	_indices.shrink_to_fit();
}

void ModelGL::Draw() const {
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexData);
	//glDrawArrays(GL_TRIANGLES, 0, numVerts);
	glDrawElements(GL_TRIANGLES, numVerts, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void ModelGL::Cleanup() {
	glDeleteBuffers(1, &vertData);
	glDeleteBuffers(1, &indexData);
	glDeleteVertexArrays(1, &vao);
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

