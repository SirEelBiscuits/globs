#include <iostream>

#include "vert.h"

size_t Vert::Offsets[AS_INDEX(VertComponent::Count)+1] = {
	0,
	sizeof(glm::vec3),
	sizeof(glm::vec3) + sizeof(glm::vec4),
	sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec2),
	sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec2)
		+ sizeof(glm::vec2)
};

StringIntern stringFromVertComponent(VertComponent const VC) {
	//I love that this works in C++11
	static StringIntern strings[AS_INDEX(VertComponent::Count)+1] =
	{
		StringIntern::Create("position"),
		StringIntern::Create("colour"),
		StringIntern::Create("texture"),
		StringIntern::Create("normal"),
		StringIntern::Create("")
	};

	return strings[AS_INDEX(VC)];
}

size_t Vert::getStride() {
	return getOffset(VertComponent::Count);
}

size_t Vert::getOffset(VertComponent Component) {
	return Offsets[+Component];
}

int Vert::getElementWidths(VertComponent Component) {
	/*
	 * TODO: Ugly code
	 * This is ugly, and assumes that vec[2,3,4] have the same
	 * underlying type which I think is true. It would be better to pull
	 * the relevant type from the glm library, but the documentation is
	 * less than helpful, and the source is unreadable.
	 */
	return (Offsets[AS_INDEX(Component) + 1]
			- Offsets[AS_INDEX(Component)])
		/ sizeof(decltype(v.x));
}

void Vert::list() const {
	std::cout << "vert {\n";
	std::cout << "\tv " << v[0] << " " << v[1] << " " << v[2] << ",\n";
	std::cout << "\tc " << c[0] << " " << c[1] << " " << c[2] << " "
		<< c[3] << ",\n";
	std::cout << "\tt " << t[0] << " " << t[1] << ",\n";
	std::cout << "\tn " << n[0] << " " << n[1] << "\n";
	std::cout << "}" << std::endl;
}

