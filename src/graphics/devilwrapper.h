#pragma once
#include "iimageloader.h"

/**
 * Wraps the DevIL calls, to aid abstractability.
 *
 * This class uses RAII, so the file will be loaded on instantiation, and
 * the file closed on destruction.
 */
class DevILWrapper : public IImageLoader {
public:
	/**
	 * Aquire the named file, and load the contained image.
	 *
	 * This can fail, but the class will just return a zero sized image
	 * when queried, if this happens.
	 */
	                     DevILWrapper(char const* fileName);
	virtual              ~DevILWrapper() override;

	/**
	 * \return nullptr if load failed, a data poiter otherwise. Do not
	 * delete this pointer!
	 */
	virtual void*        getDataPointer() override;

	/**
	 * \return 0 on image load failed, image width otherwise
	 */
	virtual unsigned int getWidth() const override;

	/**
	 * \return 0 on image load failed, image height otherwise
	 */
	virtual unsigned int getHeight() const override;
private:
	bool failed;
	unsigned int imgName;
};
