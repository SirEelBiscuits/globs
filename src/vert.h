#pragma once

#include "glm.h"
#include "utility.h"
#include "stringintern.h"

enum class VertComponent {
	Position,
	Colour,
	Texture,
	Normal,
	Count
};
MAKE_INDEX(VertComponent);

StringIntern stringFromVertComponent(VertComponent const vc);

//This is both a container for vertex data, and a provider
// of information about its data structure. Do not let these
// parts get out of sync.
//
//This may need abstracting to allow variability per model
// in future
struct Vert {
	glm::vec3 v;
	glm::vec4 c;
	glm::vec2 t;
	glm::vec2 n;

	void list() const;

	static size_t getStride();
	static size_t getOffset(VertComponent Component);
	static int getElementWidths(VertComponent Component);

	// +1 so the last element contains the stride
	static size_t Offsets[AS_INDEX(VertComponent::Count)+1];
};

