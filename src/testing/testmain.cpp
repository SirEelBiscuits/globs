#include "testsuite/testsuite.h"

#include "../graphics/iimageloader.h"
#include "../graphics/devilwrapper.h"
#include "../graphics/textureloader.h"

BEGIN_TEST_DEF(DevILWrapperTest) {
	//IImageLoader& obj = DevILWrapper("test.jpg");
	DevILWrapper obj("test.jpg");
	ASSERT_NEQ(0u, obj.getWidth());
	ASSERT_NEQ(0u, obj.getHeight());
	ASSERT_NEQ((void*)nullptr, obj.getDataPointer());
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
	Texture* tex = TextureLoader::LoadTexture(fakeIL());
	ASSERT_EQ(tex->getWidth(), il.getWidth());
	ASSERT_EQ(tex->getHeight(), il.getHeight());
	tex->cleanup();
	delete tex;
	return true;
}
END_TEST_DEF(TextureLoaderTest);

namespace UnitTesting {
	bool RunTests() {
		return Testing::RunAllTests();
	}
}
