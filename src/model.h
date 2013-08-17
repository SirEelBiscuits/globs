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

		static constexpr int getStride();
		static constexpr int getOffset(VertComponent Component);

		// +1 so the last element contains the stride
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

	//Once this function is called, any action which will change the size of
	// the contained arrays will fail, as these can potentially move the data
	// in memory which can be catastrophic to OpenGL!
	//
	//Changing the contents of the arrays is still ok though
	void Finalise() { _const = true; }

private:
	bool _const = false;
	std::vector<Vert> _verts;
	std::vector<uint16_t>  _indices;

	bool isConst();
};

MAKE_INDEX(Model::VertComponent);

