#include "iimageloader.h"

class DevILWrapper : public IImageLoader {
public:
	DevILWrapper(char const* fileName);
	virtual ~DevILWrapper() override;
	virtual void* getDataPointer() override;
	virtual int   getWidth() const override;
	virtual int   getHeight() const override;
private:
	bool failed;
	ILuint imgName;
}
