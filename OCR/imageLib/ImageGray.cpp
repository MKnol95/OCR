#include "ImageGray.h"

namespace ImageLib
{
	ImageGray::ImageGray() : Image(0, 0, 1){}

	ImageGray::ImageGray(unsigned int width, unsigned int height)
		: Image(width, height, 1)
	{

	}

	ImageGray::ImageGray(unsigned int width, unsigned int height, const std::vector<unsigned char> & data)
		: Image(width, height, data)
	{

	}

	ImageGray::ImageGray(unsigned int width, unsigned int height, const unsigned char * data)
		: Image(width, height, 1, data)
	{

	}

	ImageGray::~ImageGray() {
	}

	unsigned char * ImageGray::data(unsigned int x, unsigned int y)
	{
		return data_.data() + x + y * width();
	}

	const unsigned char * ImageGray::data(unsigned int x, unsigned int y) const
	{
		return data_.data() + x + y * width();
	}

	unsigned char & ImageGray::at(unsigned int x, unsigned int y)
	{
		return *(data_.data() + x + y * width());
	}

	unsigned char ImageGray::at(unsigned int x, unsigned int y) const
	{
		return *(data_.data() + x + y * width());
	}
}