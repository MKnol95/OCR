#include "ImageLoader.h"
#include "ImageGray.h"
#include "ImageRGB.h"
#include <corona.h>
#include <exception>
#include <memory>

using namespace ImageLib;

namespace ImageLib
{
	/*std::unique_ptr<ImageGray> loadImg(std::string filename)
	{
		corona::Image* image = corona::OpenImage(filename.c_str(), corona::PF_R8G8B8);
		
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
	*/
	std::unique_ptr<ImageRGB> loadImg(std::string filename)
	{
		corona::Image* image = corona::OpenImage(filename.c_str(), corona::PF_R8G8B8);

		if (!image) {
			throw new std::runtime_error("Image is not rgb");
		}
		unsigned char * pixels = (unsigned char *)image->getPixels();
		std::unique_ptr<ImageRGB> img = std::make_unique<ImageRGB>(image->getWidth(), image->getHeight());

		for (int x = 0; x < image->getWidth(); x++) {
			for (int y = 0; y < image->getHeight(); y++) {
				unsigned char * pixel = pixels + (y * (image->getWidth() * 3)) + (x * 3);
				img->at(x, y, Channel::Red) = pixel[0];
				img->at(x, y, Channel::Green) = pixel[1];
				img->at(x, y, Channel::Blue) = pixel[2];
			}
		}
		return img;
	}
}