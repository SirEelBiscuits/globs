#include "testsuite/testsuite.h"

#include "../iimageloader.h"
#include "../devilwrapper.h"
#include "../textureloader.h"

BEGIN_TEST_DEF(DevILWrapperTest) {
	IImageLoader& obj = DevILWrapper("test.jpg");
	ASSERT_NEQ(0, obj.getWidth());
	ASSERT_NEQ(0, obj.getHeight());
	ASSERT_NEQ(nullptr, obj.getDataPointer());
	return true;
}
END_TEST_DEF(DevILWrapperTest);

class fakeIL : public IImageLoader {
	virtual unsigned int getWidth() const override { return 2; }
	virtual unsigned int getHeight() const override { return 2; }
	virtual void* getDataPointer() {
		static unsigned char* img = {
			255, 255, 255, 255,   0,   0,   0, 255,
			0,   0,   0, 255, 255, 255, 255, 255
		};
		return (void*)img;
	}
	virtual ~fakeIL(){}
};
BEGIN_TEST_DEF(TextureLoaderTest) {
	fakeIL il;
	Texture* tex = TextureLoader::LoadTexture(il);
	ASSERT_EQ(tex->getWidth(), il.getWidth());
	ASSERT_EQ(tex->getHeight(), il.getHeight());
	return true;
}
END_TEST_DEF(TextureLoaderTest);
