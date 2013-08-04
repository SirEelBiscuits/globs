#include "model.h"

void Model::list() const {
	for( auto v : verts )
		v.list();
	for( int i = 0; i < indices.size(); ) {
		std::cout << "f ";
		for( int j = 0; j < 3; ++j )
			std::cout << indices[i++] << " ";
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
	std::cout << "{\n";
	std::cout << "\tv " << p[0] << " " << p[1] << " " << p[2] << ",\n";
	std::cout << "\tc " << c[0] << " " << c[1] << " " << c[2] << " " << c[3] << ",\n";
	std::cout << "\tt " << t[0] << " " << t[1] << ",\n";
	std::cout << "\tn " << n[0] << " " << n[1] << "\n";
	std::cout << "}" << std::endl;
}
