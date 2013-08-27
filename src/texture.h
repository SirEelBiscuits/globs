#pragma once

class Texture {
public:
	virtual void cleanup() = 0;
	virtual void set() const = 0;
};

