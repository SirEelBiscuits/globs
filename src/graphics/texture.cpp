#include "texture.h"

StringIntern Texture::StringFromTextureType(TextureType const tt) {
	static StringIntern strings[AS_INDEX(TextureType::Count)+1] = {
		"diffuseTex"_i,
		"normalTex"_i,
		""_i
	};
	static_assert(sizeof(strings)/sizeof(strings[0])
			== AS_INDEX(TextureType::Count)+1,
		"Did TextureType change size?"
	);
	return strings[AS_INDEX(tt)];
}
