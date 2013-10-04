#pragma once

#include <string>
#include <fstream>

#include "../util/log.h"
#include "modelgl.h"

/*
 * This is the factory for loading models.
 *
 * At the moment it is openGL 3.0 only. This should be abstracted when there
 * are more choices :)
 */
class ModelLoader {
public:
	/**
	 * Opens a file, reads it in and passes it to the other overload
	 *
	 * Didn't dupe the logic, won't dupe the docs.
	 */
	static Model* LoadModelFromFile(char const* fileName);

	/**
	 * Opens a wavefront.obj type model file.
	 *
	 * Note, format is customised, see source code
	 *
	 * \returns a model pointer to the loaded model, or nullptr if it
	 * 	failed. deleteing this object is up to the caller
	 */
	static Model* LoadModelFromBuffer(std::string const& buffer);
};

