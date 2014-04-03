#include "ImageLoader.h"
#define cimg_use_png
#define cimg_use_jpeg
#include "CImg.h"
#include <exception>

using namespace ImageLib;
using namespace cimg_library;

namespace ImageLib
{
	std::unique_ptr<ImageRGB> loadImg(std::string filename)
	{
		CImg<unsigned char> cimg(filename.c_str());

		if (cimg.spectrum() < 3) {
			throw new std::runtime_error("Image is not rgb");
		}

		return std::make_unique<ImageRGB>(cimg.width(), cimg.height(), cimg.begin());
	}
}