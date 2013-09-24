#pragma once

#include <vector>
#include <cstdint>

#include "vert.h"
#include "../util/log.h"

#include "ishader.h"

/*
 * This is a baseclass to contain the shared interface for model files.
 *  I can't imageine this needing that much added to it...
 *
 *  Times added to: 0
 */
class Model {
public:
	virtual ~Model(){}
	virtual bool draw() const = 0;
	virtual bool cleanup() = 0;
	virtual bool bind() const = 0;
	virtual bool unbind() const = 0;
	virtual bool useShader(IShader* shader) = 0;
	virtual unsigned int getID() const = 0;
};

