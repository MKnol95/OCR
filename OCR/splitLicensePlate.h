#pragma once
#include <corona.h>
#include "GlobalDefines.h"
#include <string>
#include <vector>
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
	std::vector<int> csvData;
public:
	splitLicensePlate(std::unique_ptr<ImageGray>& img);
	~splitLicensePlate();
	std::vector<int>& getCSV();
	corona::Image* getImageData();
	std::vector<ImageGray> splitLicensePlate::ProcessImage();
	void splitLicensePlate::WriteCSV(int,int);
	void splitLicensePlate::csvHorizontal();
	void splitLicensePlate::csvVertical();
};

