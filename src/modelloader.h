#pragma once

#include <string>
#include <fstream>

#include "log.h"
#include "modelgl.h"

/*
 * This is the factory for loading models.
 *
 * At the moment it is openGL 3.0 only. This should be abstracted when there
 *  are more choices :)
 */
class ModelLoader {
public:
	static Model* LoadModelFromFile(char const* fileName);
	static Model* LoadModelFromBuffer(std::string const& buffer);
};

