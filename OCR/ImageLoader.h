#pragma once
#include <string>
#include <memory>
#include "ImageRGB.h"

namespace ImageLib
{
	std::unique_ptr<ImageRGB> loadImg(std::string filename);
}