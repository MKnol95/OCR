#pragma once
#include <corona.h>
#include "GlobalDefines.h"
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include "imageLib\ImageGray.h"

using namespace ImageLib;
//! class SplitLicensePlate
//
//! @authors Rick van der Paauw, Marco Knol, Melvin van den Berg and Michael Pieneman
//! This class contains splitting of the characters and the creation of the histograms. 
//! This histograms are used for character recognition.
class splitLicensePlate
{
private:
	//! @var image Unique pointer to the real address (reference) of image.
	std::unique_ptr<ImageGray> &image;
	//! @var CSV outputstream for CSV
	std::ofstream CSV;
	//! @var ImageSurface is the total number of pixels.
	//! @var Height is the height of the image.
	//! @var Width is the width of the image.
	int imageSurface, height, width;
	//! @var csvData is the vector of the csvData.
	std::vector<int> csvData;
public:
	//! SplitLicensePlate constructor
	//
	//! @param img is a unique pointer to the image.
	//! The splitLicensePlate-object will get the width and height of the given image.
	splitLicensePlate(std::unique_ptr<ImageGray>& img);
	//! SplitLicensePlate destructor
	//
	//! Destructs splitLicensePlate-object.
	~splitLicensePlate();
	//! Get the CSV-pointer
	//
	//! Return the pointer to the array of the CSV data. 
	std::vector<int>& getCSV();
	//! Process the splitLicensePlate-object
	//
	//! This function cuts the characters out of the image and fills the csvData with the number of black pixels. 
	std::vector<ImageGray> splitLicensePlate::ProcessImage();
	//! Write CSV 
	//
	//! @param x is the csv-genre: total horizontal (0), horizontal (1) or vertical (2). 
	//! @param y is the number of the character. 
	//! Write the CSV-files for the total horizontal image, the horizontal per char and the vertical per char.
	void splitLicensePlate::WriteCSV(int x,int y);
	//! horizontal CSV fill 
	//
	//! Fill the CSV-data with the number of black pixels on the horizontal line (columns).
	void splitLicensePlate::csvHorizontal();
	//! vertical CSV fill 
	//
	//! Fill the CSV-data with the number of black pixels on the vertical line (rows).
	void splitLicensePlate::csvVertical();
};

