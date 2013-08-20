#pragma once

#include <string>
#include <fstream>

#include "log.h"
#include "modelgl.h"

/*
 * For now, this class loads models for openGL usage only :)
 */
class ModelLoader {
public:
	static Model* LoadModelFromFile(char const* fileName);
	static Model* LoadModelFromBuffer(std::string const& buffer);
};

