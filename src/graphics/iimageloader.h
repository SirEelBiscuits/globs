#pragma once

/**
 * Image loader interface.
 *
 * This defines the basic things about a loaded image we need to know to be
 * able to put that image into openGL. The image needs to be loaded into an
 * RGBA format.
 */
class IImageLoader {
public:
	/**
	 * Data should have the format of 4 bytes per pixel
	 *
	 * \return pointer to the start of the image data.
	 */
	virtual void*        getDataPointer() = 0;

	/**
	 * \return the width of the image, in pixels.
	 */
	virtual unsigned int getWidth() const = 0;

	/**
	 *  \return the height of the image, in pixels.
	 */
	virtual unsigned int getHeight() const = 0;

	/**
	 * Virtual destructor, in case derived classes need it.
	 */
	virtual              ~IImageLoader(){}
};
