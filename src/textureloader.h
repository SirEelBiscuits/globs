#pragma once

#include "texture.h"

class TextureLoader {
public:
	static Texture* LoadTextureFromFile(char const* fileName);
};
