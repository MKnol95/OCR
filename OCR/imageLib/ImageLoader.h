#pragma once
#include <string>
#include <memory>
#include "ImageGray.h"
#include "ImageRGB.h"

namespace ImageLib
{
	//std::unique_ptr<ImageGray> loadImg(std::string filename);
	std::unique_ptr<ImageRGB> loadImg(std::string filename);
}