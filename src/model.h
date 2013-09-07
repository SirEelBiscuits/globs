#pragma once

#include <vector>
#include <cstdint>

#include "vert.h"
#include "log.h"

/*
 * This is a baseclass to contain the shared interface for model files.
 *  I can't imageine this needing that much added to it...
 *
 *  Times added to: 0
 */
class Model {
public:
	virtual void Draw() const = 0;
	virtual void Cleanup() = 0;
};

