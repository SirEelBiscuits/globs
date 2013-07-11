#pragma once

#include <vector>
#include "glm.h"
#include <cstdint>

#include "log.h"

class Model {
public:
	std::vector<glm::vec3> verts;
	std::vector<uint16_t>  indices;

	void list() const;
};

