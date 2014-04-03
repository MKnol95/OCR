#include "Image.h"

namespace ImageLib
{
	Image::Image(unsigned int width, unsigned int height, int numChannels)
		: width_(width), height_(height), data_(width * height * numChannels)
	{

	}

	Image::Image(unsigned int width, unsigned int height, const std::vector<unsigned char> & data)
		: width_(width), height_(height), data_(data)
	{

	}

	Image::Image(unsigned int width, unsigned int height, int numChannels, const unsigned char * data)
		: width_(width), height_(height), data_(data, data + width * height * numChannels)
	{

	}
}