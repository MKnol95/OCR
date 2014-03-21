#pragma once
#include <corona.h>
#include "GlobalDefines.h"
#include <string>
#include <fstream>
#include <memory>

class splitLicensePlate
{
private:
	corona::Image *originalImage, *splitImage;
	byte *originalPixels, *splitPixels;
	std::ofstream splitCSV;
	int imageSurface, height, width;
	int splitCSVSplit[2000];
public:
	splitLicensePlate();
	~splitLicensePlate();
	int* getSplitCSVSplit();
	corona::Image* getImageData();
	void ProcessImage();
	void WriteCSV();
};

