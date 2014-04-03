#pragma once
#include <corona.h>
#include "GlobalDefines.h"
#include <string>
#include <fstream>
#include <memory>
#include "imageLib\ImageGray.h"

using namespace ImageLib;

class splitLicensePlate
{
private:
	std::unique_ptr<ImageGray> &image;

	std::ofstream splitCSV;
	int imageSurface, height, width;
	int splitCSVSplit[2000];
public:
	splitLicensePlate(std::unique_ptr<ImageGray>& img);
	~splitLicensePlate();
	int* getSplitCSVSplit();
	corona::Image* getImageData();
	std::vector<ImageGray> ProcessImage();
	void WriteCSV();
};

