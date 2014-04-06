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
	std::ofstream CSV;
	int imageSurface, height, width;
	int csvData[2000];
public:
	splitLicensePlate(std::unique_ptr<ImageGray>& img);
	~splitLicensePlate();
	int* getCSV();
	corona::Image* getImageData();
	std::vector<ImageGray> splitLicensePlate::ProcessImage();
	void splitLicensePlate::WriteCSV(int,int);
	int* splitLicensePlate::csvHorizontal();
	int* splitLicensePlate::csvVertical();
};

