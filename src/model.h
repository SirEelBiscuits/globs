#pragma once

#include <vector>
#include <cstdint>

#include "vert.h"
#include "log.h"

class Model {
public:
	virtual void list() const = 0;
	virtual void Draw() const = 0;
	virtual void Cleanup() = 0;
};

