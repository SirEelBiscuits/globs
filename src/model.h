#pragma once

#include <vector>
#include "glm.h"
#include <cstdint>

#include "log.h"
#include "utility.h"

class Model {
public:
	enum class VertComponent {
		Position,
		Colour,
		Texture,
		Normal,
		Count
	};

	struct Vert {
		glm::vec3 p;
		glm::vec4 c;
		glm::vec2 t;
		glm::vec2 n;

		void list() const;

		static constexpr int getStride();
		static constexpr int getOffset(VertComponent Component);

		static constexpr int Offsets[AS_INDEX(VertComponent::Count)+1] = {
			0,
			sizeof(glm::vec3),
			sizeof(glm::vec3) + sizeof(glm::vec4),
			sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec2),
			sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec2) + sizeof(glm::vec2)
		};
	};

	std::vector<Vert> verts;
	std::vector<uint16_t>  indices;

	void list() const;
};

MAKE_INDEX(Model::VertComponent);

