#pragma once
#include "iimageloader.h"

class DevILWrapper : public IImageLoader {
public:
	                     DevILWrapper(char const* fileName);
	virtual              ~DevILWrapper() override;
	virtual void*        getDataPointer() override;
	virtual unsigned int getWidth() const override;
	virtual unsigned int getHeight() const override;
private:
	bool failed;
	unsigned int imgName;
};
