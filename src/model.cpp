#include "model.h"

void Model::list() const {
	for( auto v : verts )
		std::cout << "v " << v[0] << " " << v[1] << " " << v[2] << std::endl;
	for( int i = 0; i < indices.size(); ) {
		std::cout << "f ";
		for( int j = 0; j < 3; ++j )
			std::cout << indices[i++] << " ";
		std::cout << std::endl;
	}
}
