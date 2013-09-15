#pragma once

class IImageLoader {
public:
	virtual void*        getDataPointer() = 0;
	virtual unsigned int getWidth() const = 0;
	virtual unsigned int getHeight() const = 0;
	virtual              ~IImageLoader(){}
};
