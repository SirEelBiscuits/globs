#pragma once

#include <vector>
#include <cstdint>

#include "vert.h"
#include "../util/log.h"

#include "ishader.h"

/**
 * Model interface class.
 *
 * This object is to hold model data only.
 *
 * This shouldn't need adding to, as it's fairly simple
 * Times added to: 2
 */
class Model {
public:
	/**
	 * virtual destructor in case its required by deriving classes.
	 */
	virtual ~Model(){}

	/**
	 * Draw this model with the current shader, textures, uniforms &c.
	 *
	 * \return true if no errors reported.
	 */
	virtual bool draw() const = 0;

	/**
	 * Delete the resources used by this model.
	 *
	 * \return true if no errors reported.
	 */
	virtual bool cleanup() = 0;

	/**
	 * Bind this model's data for use.
	 *
	 * \return true if no errors reported.
	 */
	virtual bool bind() const = 0;

	/**
	 * Unbind this model's data for use
	 *
	 * Note, this could be static in many cases..
	 *
	 * \return true if no errors reported.
	 */
	virtual bool unbind() const = 0;

	/**
	 * Bind the shader for use.
	 *
	 * This may be an openGLism.
	 *
	 * \return true if no errors reported.
	 */
	virtual bool useShader(IShader* shader) = 0;

	/**
	 * \return a unique id for the object
	 */
	virtual unsigned int getID() const = 0;
};

