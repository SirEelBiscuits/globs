class IImageLoader {
public:
	virtual void* getDataPointer() = 0;
	virtual int   getWidth() const = 0;
	virtual int   getHeight() const = 0;
	virtual void  ~IImageLoader() = 0;
};
