#pragma once
#include "imageLib\ImageGray.h"
#include <memory>
#include <corona.h>
#define NUMBER_OF_CHARACTERS 37
#define FIND_CHAR_PERCENTAGE 99
#define	CHAR_INDEX_SIZE	26
#define LAST_FOUND_STRIPE 0
#define	LAST_FOUND_LETTER 1
#define	LAST_FOUND_NUMBER 2
#define Q_INDEX 16
#define O_INDEX 14
#define ASCII_CONVERT_LETTER 65
#define ASCII_CONVERT_NUMBER 21
#define ASCII_CONVERT_STRIPE 19

using namespace ImageLib;
class OCRPatternMatching
{
private:
	unsigned char lastDetection;
	std::vector<std::unique_ptr<ImageGray>> referenceImages;
	ImageGray Resample(ImageGray& input, short newWidth, short newHeight);
	unsigned char Recognize(ImageGray& character);
public:
	OCRPatternMatching();
	std::string RecognizeLicenseplate(std::vector<ImageGray>& chars);
};

