#include "ImageRGB.h"

namespace ImageLib
{
	ImageRGB::ImageRGB(unsigned int width, unsigned int height)
		: Image(width, height, 3), channelsize(width * height)
	{

	}

	ImageRGB::ImageRGB(unsigned int width, unsigned int height, const std::vector<unsigned char> & data)
		: Image(width, height, data), channelsize(width * height)
	{

	}

	ImageRGB::ImageRGB(unsigned int width, unsigned int height, const unsigned char * data)
		: Image(width, height, 3, data), channelsize(width * height)
	{

	}

	unsigned char * ImageRGB::data(unsigned int x, unsigned int y, Channel channel)
	{
		return data_.data() + x + (y * width()) + ((int)channel * channelsize);
	}

	const unsigned char * ImageRGB::data(unsigned int x, unsigned int y, Channel channel) const
	{
		return data_.data() + x + (y * width()) + ((int)channel * channelsize);
	}

	ImageRGB::pointer ImageRGB::data(unsigned int x, unsigned int y)
	{
		auto ptr_red = data(x, y, Channel::Red);
		auto ptr_green = ptr_red + channelsize;
		auto ptr_blue = ptr_green + channelsize;

		return ImageRGB::pointer(ptr_red, ptr_green, ptr_blue);
	}

	ImageRGB::const_pointer ImageRGB::data(unsigned int x, unsigned int y) const
	{
		auto ptr_red = data(x, y, Channel::Red);
		auto ptr_green = ptr_red + channelsize;
		auto ptr_blue = ptr_green + channelsize;

		return ImageRGB::const_pointer(ptr_red, ptr_green, ptr_blue);
	}

	ImageRGB::reference ImageRGB::at(unsigned int x, unsigned int y)
	{
		auto ptrs = data(x, y);

		return ImageRGB::reference(*ptrs.red, *ptrs.green, *ptrs.blue);
	}

	ImageRGB::const_reference ImageRGB::at(unsigned int x, unsigned int y) const
	{
		auto ptrs = data(x, y);

		return ImageRGB::const_reference(*ptrs.red, *ptrs.green, *ptrs.blue);
	}

	unsigned char & ImageRGB::at(unsigned int x, unsigned int y, Channel channel)
	{
		auto ptr = data(x, y, channel);

		return *ptr;
	}

	unsigned char ImageRGB::at(unsigned int x, unsigned int y, Channel channel) const
	{
		auto ptr = data(x, y, channel);

		return *ptr;
	}
}