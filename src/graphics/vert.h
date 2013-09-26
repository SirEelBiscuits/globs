#pragma once

#include "glm.h"
#include "../util/utility.h"
#include "../util/stringintern.h"

/**
 * Vertex attributes that might be used
 *
 * This will be associated with input variables to shaders, as well as slots
 * in the vert object. Although at the moment there is only a single
 * implementation of the Vert object, and it supports them all.
 *
 * For a variable to be associated with a slot, it must have the exact
 * correct name, see the implementation of Vert::StringFromVertComponent
 * \sa vert.cpp
 */
enum class VertComponent {
	Position,
	Colour,
	Texture,
	Normal,
	Count
};
MAKE_INDEX(VertComponent);

/**
 * Container for vert data
 *
 * This is both a container for vertex data, and a provider of information
 *  about its data structure. Do not let these parts get out of sync.
 *
 * This may need abstracting to allow variability per model in future,
 *  although with the static functions, templates may be the sanest way to
 *   achieve this.
 */
struct Vert {
	/**
	 * stores the position element of the vertex
	 */
	glm::vec3 v;	// 3*4 = 12
	/**
	 * stores the colour element of the vertex
	 */
	glm::vec4 c;	// 4*4 = 16
	/**
	 * stores the uv position of the vertex
	 */
	glm::vec2 t;	// 2*4 =  8
	/**
	 * stores the normal uv position of the vertex
	 */
	glm::vec2 n;	// 2*4 =  8
			// Total:44

	/**
	 * output the data, formatted for readability.
	 */
	void list() const;

	/**
	 * This is effectively the same as sizeof(decltype(this))
	 */
	static size_t getStride();

	/**
	 * \returns the offset of a particular component in this type
	 */
	static size_t getOffset(VertComponent Component);

	/**
	 * \returns the number of elements in the requested vector
	 */
	static int getElementWidths(VertComponent Component);

	/**
	 * \returns a StringIntern which is the name shader arguments that
	 * take this vert component value should be given. For the actual
	 * values, see the source code.
	 * \sa vert.cpp
	 */
	static StringIntern StringFromVertComponent(VertComponent const vc);

private:
	// +1 so the last element contains the stride
	static size_t Offsets[AS_INDEX(VertComponent::Count)+1];
};

