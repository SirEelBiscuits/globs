#include "devilwrapper.h"
#include "log.h"

#define LOG "IL"

DevILWrapper::DevILWrapper(char const* fileName)
	: failed(false)
{
	LOG_MSG(LOG, "Initialising devIL");
	ilInit();
	iluInit();

	ilGenImages(1, &imgName);
	ilBindImage(imgName);

	LOG_MSG(LOG, "Loading image");
	if(!ilLoadImage(fileName)) {
		LOG_MSG(LOG, "Image load (%s) failed.", fileName);
		failed = true;
		ilDeleteImages(1, &imgName);
		return;
	}

	LOG_MSG(LOG, "Enforcing format rules");
	if(ilGetInteger(IL_IMAGE_FORMAT) != IL_RGBA) {
		LOG_MSG(LOG, "Changing pixel format");
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	}
	ILinfo imgInfo;
	iluGetImageInfo(&imgInfo);
	if(imgInfo.Origin == IL_ORIGIN_UPPER_LEFT) {
		LOG_MSG(log.toString(), "Flipping image");
		iluFlipImage();
	}
	LOG_MSG(log.toString(), "Formatting complete");
}

DevILWrapper::~DevIlWrapper() override {
	if(failed)
		return;
	ilDeleteImages(1, &imgName);
}

void* getDataPointer() override {
	if(failed)
		return nullptr;
	ilBindImage(imgName);
	void* ret = ilGetData();
	if(ret == nullptr)
		LOG_MSG("ERROR", "DevIL returned null value!");
	return ret\
}

int DevILWrapper::getWidth() const override {
	if(failed)
		return 0;
	ilBindImage(imgName);
	return ilGetInteger(IL_IMAGE_WIDTH);
}

int DevILWrapper::getHeight() const override {
	if(failed)
		return 0;
	ilBindImage(imgName);
	return ilGetInteger(IL_IMAGE_HEIGHT);
}
