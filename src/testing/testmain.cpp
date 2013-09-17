#include "testsuite/testsuite.h"

#include "../graphics/iimageloader.h"
#include "../graphics/devilwrapper.h"
#include "../graphics/textureloader.h"
#include "../graphics/ishader.h"
#include "../graphics/shaderloader.h"
#include "../graphics/vert.h"

/*
 * Not indenting, as it adds next to no information. The namespace is to
 * prevent testing code from polluting the rest of the project
 */
namespace UnitTesting {

BEGIN_TEST_DEF(DevILWrapperTest) {
	//IImageLoader& obj = DevILWrapper("test.jpg");
	DevILWrapper obj("test.jpg");
	ASSERT_NEQ(0u, obj.getWidth());
	ASSERT_NEQ(0u, obj.getHeight());
	ASSERT_NEQ(static_cast<void*>(nullptr), obj.getDataPointer());
	return true;
}
END_TEST_DEF(DevILWrapperTest);

class fakeIL : public IImageLoader {
public:
	fakeIL(){}
	virtual unsigned int getWidth() const override { return 2; }
	virtual unsigned int getHeight() const override { return 2; }
	virtual void* getDataPointer() {
		static unsigned char img[] = {
			255, 255, 255, 255,   0,   0,   0, 255,
			0,   0,   0, 255, 255, 255, 255, 255
		};
		return (void*)img;
	}
	virtual ~fakeIL(){}
};

BEGIN_TEST_DEF(TextureLoaderTest) {
	fakeIL il;
	Texture* tex = TextureLoader::LoadTexture(fakeIL(),
		TextureType::Diffuse
	);
	ASSERT_EQ(tex->getWidth(), il.getWidth());
	ASSERT_EQ(tex->getHeight(), il.getHeight());
	tex->cleanup();
	delete tex;
	return true;
}
END_TEST_DEF(TextureLoaderTest);

BEGIN_TEST_DEF(ShaderTest) {
	/*
	 * This is the first test I've attempted to write before the code it
	 * will test has been written. Forgive me :)
	 */
	std::vector<IShader*> v;
	v.push_back(ShaderLoader::GetBasicShader());
	std::string frag(
R"(#version 150
in vec4 cfv;
in vec2 tfv;
out vec4 oc;
uniform sampler2D ts;
void main() {
	oc = cfs*texture(ts,tfv);
})"
	);
	std::string vert(
R"(#version 150
in vec4 position;
in vec4 colour;
out vec4 cfv;
in vec2 texture;
out vec2 tfv;
void main() {
	gl_Position = position;
	cfv = colour;
	tfv = texture;
})"
	);
	v.push_back(ShaderLoader::LoadShaderFromBuffers(frag,vert));

	for(auto s: v) {
		ASSERT_NEQ(static_cast<decltype(s)>(nullptr), s);
		ASSERT_GT (0u, s->getShaderID());
		for(auto a: {
				VertComponent::Position,
				VertComponent::Colour,
				VertComponent::Texture
			}
		) {
			ASSERT_NEQ(false, s->isAttributeSupported(a));
		}
		ASSERT_GT (0u, s->getNumTextureSlots());
		for(int i = 0; i < AS_INDEX(TextureType::Count); ++i) {
			if(s->isTextureTypeSupported(
				static_cast<TextureType>(i)
			)) {
				ASSERT_GT(0u, s->getTextureSlot(
					static_cast<TextureType>(i)
				));
			}
		}
	}
	return true;
}
END_TEST_DEF(ShaderTest);

bool RunTests() {
	return Testing::RunAllTests();
}

} //end namespace UnitTesting
