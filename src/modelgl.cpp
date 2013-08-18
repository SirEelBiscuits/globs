#include "modelgl.h"
#include "vert.h"
#include "shader.h"

#include <iostream>

void ModelGL::FinaliseLoad() {
	_const = true;

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
}

void ModelGL::Draw() const {
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexData);
	//glDrawArrays(GL_TRIANGLES, 0, numVerts);
	glDrawElements(GL_TRIANGLES, numVerts, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void ModelGL::Cleanup() {

}

void ModelGL::list() const {
	for(auto v : _verts)
		v.list();
	// i incremented inside inner loop, as faces are stored all smooshed
	for(unsigned int i = 0; i < _indices.size();) {
		std::cout << "f ";
		for(int j = 0; j < 3; ++j)
			std::cout << _indices[i++] << " ";
		std::cout << std::endl;
	}
}

//These are for ease of creating debug/release targets later
#define CONST_CHECK if(!isConst())
#define CHECK_ELSE else

Vert ModelGL::getOrCreateVert(unsigned int Index) {
	if(Index >= _verts.size()) {
		CONST_CHECK {
			_verts.resize(Index + 1);
			return _verts[Index];
		}
		CHECK_ELSE
			return _verts[0];
	}
	return _verts[Index];
}

Vert ModelGL::getVert(unsigned int Index) const {
	return _verts[Index];
}

void ModelGL::setVert(unsigned int Index, Vert newValue) {
	//no const check - shouldn't be able to affect vector size
	_verts[Index] = newValue; //do your own damn bounds check
}

int ModelGL::getIndex(unsigned int Index) const {
	return _indices[Index];
}

void ModelGL::setIndex(unsigned int Index, uint16_t newValue) {
	_indices[Index] = newValue;
}

void ModelGL::appendIndex(uint16_t newIndex) {
	CONST_CHECK {
		_indices.push_back(newIndex);
	}
}

#undef CONST_CHECK
#undef CHECK_ELSE

bool ModelGL::isConst() {
	// TODO Assert or spew or something?
	return _const;
}
