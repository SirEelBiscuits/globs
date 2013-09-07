#pragma once

#include "texture.h"

/*
 * Factory for textures. Currently only returns OpenGL textures. This should
 * be abstracted later if there are more options.
 */
class TextureLoader {
public:
	static Texture* LoadTextureFromFile(char const* fileName);
};
