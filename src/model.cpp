#include "model.h"

void Model::list() const {
	for( auto v : _verts )
		v.list();
	for( unsigned int i = 0; i < _indices.size(); ) { // i incremented inside inner loop
		std::cout << "f ";
		for( int j = 0; j < 3; ++j )
			std::cout << _indices[i++] << " ";
		std::cout << std::endl;
	}
}

constexpr int Model::Vert::getStride() {
	return getOffset(VertComponent::Count);
}

constexpr int Model::Vert::getOffset( Model::VertComponent Component ) {
	return Offsets[+Component];
}

void Model::Vert::list() const {
	std::cout << "vert {\n";
	std::cout << "\tv " << v[0] << " " << v[1] << " " << v[2] << ",\n";
	std::cout << "\tc " << c[0] << " " << c[1] << " " << c[2] << " " << c[3] << ",\n";
	std::cout << "\tt " << t[0] << " " << t[1] << ",\n";
	std::cout << "\tn " << n[0] << " " << n[1] << "\n";
	std::cout << "}" << std::endl;
}

#define CONST_CHECK if( !isConst() )
#define CHECK_ELSE else

Model::Vert Model::getOrCreateVert(unsigned int Index) {
	if( Index >= _verts.size() ) {
		CONST_CHECK {
			_verts.resize(Index + 1);
			return _verts[Index];
		}
		CHECK_ELSE
			return _verts[0];
	}
	return _verts[Index];
}

Model::Vert Model::getVert(unsigned int Index) const {
	return _verts[Index];
}

void Model::setVert(unsigned int Index, Vert newValue) {
	//no const check - shouldn't be able to affect vector size
	_verts[Index] = newValue; //do your own damn bounds check
}

uint16_t Model::getIndex(unsigned int Index) const {
	return _indices[Index];
}

void Model::setIndex(unsigned int Index, uint16_t newValue) {
	_indices[Index] = newValue;
}

void Model::appendIndex(uint16_t newIndex) {
	CONST_CHECK {
		_indices.push_back(newIndex);
	}
}

bool Model::isConst() {
	// TODO Assert or spew or something?
	return _const;
}
