#pragma once

/*
 * This is a base class to contain the shared interface for textures.
 *  I can't imagine it needing much adding to it.
 *
 *  Times added to: 0
 */
class Texture {
public:
	virtual void cleanup() = 0;
	virtual void set() const = 0;
	virtual unsigned int getWidth() const = 0;
	virtual unsigned int getHeight() const = 0;
};

