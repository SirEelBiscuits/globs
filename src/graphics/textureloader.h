#pragma once

#include "texture.h"
#include "imageloader.h"

/**
 * Factory for textures.
 *
 * Currently only returns OpenGL textures. This should be abstracted later
 * when there are more options.
 */
class TextureLoader {
public:
	/**
	 * Turn the image an ImageLoader has loaded into a GL texture
	 *
	 * \param il an image loader, that has already loaded an image.
	 * \param type the type of texture this is to be used as.
	 * \returns nullptr if the image load failed
	 */
	static Texture* LoadTexture(ImageLoader&& il, TextureType type);
};
