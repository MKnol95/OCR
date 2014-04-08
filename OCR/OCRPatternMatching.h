#pragma once
#include "imageLib\ImageGray.h"
#include <memory>
#include <corona.h>
#define NUMBER_OF_CHARACTERS 37

using namespace ImageLib;
class OCRPatternMatching
{
private:
	std::vector<std::unique_ptr<ImageGray>> referenceImages;
	ImageGray Resample(ImageGray& input, int newWidth, int newHeight);
public:
	OCRPatternMatching();
	unsigned char Recognize(ImageGray& character);
};

