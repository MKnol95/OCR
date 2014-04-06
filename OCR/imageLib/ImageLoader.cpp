#include "ImageLoader.h"
#include "ImageGray.h"
#include "ImageRGB.h"
#include <corona.h>
#include <exception>
#include <memory>

using namespace ImageLib;

namespace ImageLib
{
	std::unique_ptr<ImageGray> loadImg(std::string filename)
	{
		corona::Image* image = corona::OpenImage(filename.c_str(), corona::PF_R8G8B8);
		// is it really working?
		if (!image) {
			throw new std::runtime_error("Image is not rgb");
		}
		unsigned char * pixels = (unsigned char *)image->getPixels();
		std::unique_ptr<ImageGray> img = std::make_unique<ImageGray>(image->getWidth(), image->getHeight());
		int count = 0;
		for (std::vector<unsigned char>::iterator it = img->begin(); it != img->end(); ++it) {
			unsigned char color = (unsigned char)((int)(pixels[count] + pixels[count + 1] + pixels[count + 2]) / 3);
			*it = color;
			count += 3;
		}
		return img;
	}
}