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
		glm::vec3 v;
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

	void list() const;
	Vert getOrCreateVert(unsigned int Index);
	Vert getVert(unsigned int Index) const;
	void setVert(unsigned int Index, Vert newValue);
	uint16_t getIndex(unsigned int Index) const;
	void setIndex(unsigned int Index, uint16_t newValue);
	void appendIndex(uint16_t newIndex);
	void Finalise() { _const = true; }

private:
	bool _const = false;
	std::vector<Vert> _verts;
	std::vector<uint16_t>  _indices;

	bool isConst();
};

MAKE_INDEX(Model::VertComponent);

