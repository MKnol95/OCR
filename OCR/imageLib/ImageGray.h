#pragma once
#include "Image.h"

namespace ImageLib 
{
	class ImageGray : public Image
	{
	public:
		ImageGray();
		ImageGray(unsigned int width, unsigned int height);
		ImageGray(unsigned int width, unsigned int height, const std::vector<unsigned char> & data);
		ImageGray(unsigned int width, unsigned int height, const unsigned char * data);
		~ImageGray();

		int channels() const { return 1; }

		/**
		Get Pointer to pixel at (x,y)
		*/
		unsigned char * data(unsigned int x = 0, unsigned int y = 0);
		const unsigned char * data(unsigned int x = 0, unsigned int y = 0) const;

		/**
		Get reference to pixel at (x,y)
		*/
		unsigned char & at(unsigned int x, unsigned int y);
		unsigned char at(unsigned int x, unsigned int y) const;
	};
}