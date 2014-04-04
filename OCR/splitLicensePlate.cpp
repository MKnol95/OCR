#include "splitLicensePlate.h"
#include "OCR.h"
#include "imageLib\ImageGray.h"
#include <corona.h>
#include <iostream>
#include <string>
#include <fstream>
#include "GlobalDefines.h"
#include <memory.h>

using namespace ImageLib;

splitLicensePlate::splitLicensePlate(std::unique_ptr<ImageGray>& img) : image(std::move(img))
{
	//image = std::move(img);
	width = img->width();
	height = img->height();
	imageSurface = width * height;
}

splitLicensePlate::~splitLicensePlate()
{
}

int* splitLicensePlate::getSplitCSVSplit()
{
	return  splitCSVSplit;
}

std::vector<ImageGray> splitLicensePlate::ProcessImage()
{
	std::vector<ImageGray> splitimage;

	const int findArea = 20;									/////// 8 karakters + 12 vlekkeen op het kenteken die los van de characters zitten is er mogelijk voor worst case.
	splitLicensePlate::csvHorizontaal();
	int borderLeft[findArea];
	int borderRight[findArea];
	int countL = 0, countR = 0, areaFound = 0;
	for (int i = 0; i < width; i++){
		if (splitCSVSplit[i] != 0 && splitCSVSplit[i - 1] == 0) // vergelijking met de pixel ervoor.
		{
			borderLeft[countL] = i;
			countL++;

		}
		else if (i == 0 && splitCSVSplit[i] != 0) // vergelijking met de pixel ervoor.
		{
			borderLeft[countL] = i;
			countL++;

		}
		else if (splitCSVSplit[i] != 0 && splitCSVSplit[i + 1] == 0) // vergelijking mer de pixel ernaa
		{
			if (i < width){
				borderRight[countR] = i + 1;
				countR++;
				areaFound++;
			}
			else if (i == width)
			{
				borderRight[countR] = i;
				areaFound++;
			}
		}
	}
	for (int z = 0; z < areaFound; z++){
		int splitWidth = borderRight[z] - borderLeft[z];
		ImageGray character = ImageGray(splitWidth, image->height());
		for (int i = borderLeft[z]; i < borderRight[z]; i++){
			for (int j = 0; j < height; j++){
					int xSplit = (i - borderLeft[z]);
					unsigned char& pixel = character.at(xSplit, j);
					pixel = image->at(i, j);
			}
		}
		splitimage.push_back(character);
	}
	return splitimage;
}

void splitLicensePlate::WriteCSV(int x)
{
	if (x == 0){
		splitCSV.open((Data::getInstance().getPath() + "split_" + Data::getInstance().getFile() + "_histogram.csv").c_str());
		for (int i = 0; i < width; i++)
		{
			float normalized = ((float)splitCSVSplit[i]);
			splitCSV << i << ";" << normalized << "\n";
		}
		splitCSV.close();
	}
	else if (x == 1){
		horizontalCSV.open((Data::getInstance().getPath() + "horizontal_" + Data::getInstance().getFile() + "_histogram.csv").c_str());
		for (int i = 0; i < width; i++)
		{
			float normalized = ((float)splitCSVSplit[i]);
			horizontalCSV << i << ";" << normalized << "\n";
		}
		horizontalCSV.close();
	}
	else if (x == 2){
		verticalCSV.open((Data::getInstance().getPath() + "vertical_" + Data::getInstance().getFile() + "_histogram.csv").c_str());
		for (int i = 0; i < height; i++)
		{
			float normalized = ((float)splitCSVSplit[i]);
			verticalCSV << i << ";" << normalized << "\n";
		}
		verticalCSV.close();
	}
}

void splitLicensePlate::csvHorizontaal(){
	for (int i = 0; i < width; i++) {
		splitCSVSplit[i] = 0;
	}
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			byte whiteOrBlack = image->at(i, j);
			if (whiteOrBlack == 0){
				splitCSVSplit[i] += 1;
			}
		}
	}
}

void splitLicensePlate::csvVertical(){
	for (int i = 0; i < height; i++) {
		splitCSVSplit[i] = 0;
	}
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			byte whiteOrBlack = image->at(j, i);
			if (whiteOrBlack == 0){
				splitCSVSplit[i] += 1;
			}
		}
	}
}