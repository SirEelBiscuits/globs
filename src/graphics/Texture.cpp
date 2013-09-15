#include "texture.h"

StringIntern Texture::StringFromTextureType(TextureType const tt) {
	static StringIntern strings[AS_INDEX(TextureType::Count)+1] = {
		StringIntern("diffuseTex"),
		StringIntern("normalTex"),
		StringIntern("")
	};
	static_assert(sizeof(strings)/sizeof(strings[0])
			== AS_INDEX(TextureType::Count)+1,
		"Did TextureType change size?"
	);
	return strings[AS_INDEX(tt)];
}
