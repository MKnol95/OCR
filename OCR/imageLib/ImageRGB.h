#pragma once
#include "Image.h"

namespace ImageLib 
{
	enum class Channel
	{
		Red = 0,
		Green = 1,
		Blue = 2
	};

	template<typename T>
	struct Rgb
	{
		T red;
		T green;
		T blue;

		inline Rgb(T r, T g, T b)
			: red(r), green(g), blue(b) {}
	};

	class ImageRGB : public Image
	{
	private:
		size_t channelsize;
	public:
		ImageRGB(unsigned int width, unsigned int height);
		ImageRGB(unsigned int width, unsigned int height, const std::vector<unsigned char> & data);
		ImageRGB(unsigned int width, unsigned int height, const unsigned char * data);

		typedef Rgb<unsigned char &> reference;
		typedef Rgb<const unsigned char &> const_reference;

		typedef Rgb<unsigned char *> pointer;
		typedef Rgb<const unsigned char *> const_pointer;

		int channels() const { return 3; }

		/**
		Get Pointer to pixel at (x,y) in the given channel
		*/
		unsigned char * data(unsigned int x, unsigned int y, Channel channel);
		const unsigned char * data(unsigned int x, unsigned int y, Channel channel) const;

		/**
		Get struct of pointers to each channel at (x, y)
		@return [red *, green *, blue *]
		*/
		pointer data(unsigned int x, unsigned int y);
		const_pointer data(unsigned int x, unsigned int y) const;

		/**
		Get struct of references to pixel at (x,y)
		*/
		reference at(unsigned int x = 0, unsigned int y = 0);
		const_reference at(unsigned int x = 0, unsigned int y = 0) const;

		/**
		Get reference to pixel at (x,y), in the given channel
		*/
		unsigned char & at(unsigned int x, unsigned int y, Channel channel);
		unsigned char at(unsigned int x, unsigned int y, Channel channel) const;
	};
}