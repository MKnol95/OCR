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

int* splitLicensePlate::getCSV()
{
	return  csvData;
}

std::vector<ImageGray> splitLicensePlate::ProcessImage()
{
	std::vector<ImageGray> splitimage;

	const int findArea = 20;/////// 8 karakters + 12 vlekkeen op het kenteken die los van de characters zitten is er mogelijk voor worst case.
	int borderLeft[findArea];
	int borderRight[findArea];
	int countL = 0, countR = 0, areaFound = 0, above = 0, under = 0;
	splitLicensePlate::csvHorizontal();
	for (int i = 0; i < width; i++){
		if (csvData[i] != 0 && csvData[i - 1] == 0) // vergelijking met de pixel ervoor.
		{
			borderLeft[countL] = i;
			countL++;

		}
		else if (i == 0 && csvData[i] != 0) // vergelijking met de pixel ervoor.
		{
			borderLeft[countL] = i;
			countL++;

		}
		else if (csvData[i] != 0 && csvData[i + 1] == 0) // vergelijking mer de pixel ernaa
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
	/* under contruction xd
	for (int i = 0; i < height; i++){
		if (csvData[i] != 0 && csvData[i - 1] == 0) // vergelijking met de pixel ervoor.
		{
			borderLeft[countL] = i;
			countL++;

		}
		else if (i == 0 && csvData[i] != 0) // vergelijking met de pixel ervoor.
		{
			borderLeft[countL] = i;
			countL++;

		}
		else if (csvData[i] != 0 && csvData[i + 1] == 0) // vergelijking mer de pixel ernaa
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
	}*/
	for (int z = 0; z < areaFound; z++){
		int splitWidth = borderRight[z] - borderLeft[z];
		ImageGray character = ImageGray(splitWidth, image->height());
		for (int i = borderLeft[z]; i < borderRight[z]; i++){
			for (int j = 0; j < height; j++){
					int xSplit = (i - borderLeft[z]);
					unsigned char& pixel = character.at(xSplit, j);
					pixel = image->at(i, j);
			}		}
		splitimage.push_back(character);
	}
	return splitimage;
}

void splitLicensePlate::WriteCSV(int x, int y)
{
	if (x == 0 && y == 0){
		std::string path = "C:\\Images\\Split_Histogram.csv";
		CSV.open(path);
		for (int i = 0; i < width; i++)
		{
			int normalized = ((int)csvData[i]);
			CSV << i << ";" << normalized << "\n";
		}
		CSV.close();
	}
	else if (x == 1){
		std::string path = "C:\\Images\\horizontal_histogram";
		path += std::to_string(y);
		path += ".csv";
		CSV.open(path);
		for (int i = 0; i < width; i++)
		{
			float normalized = ((float)csvData[i]);
			CSV << i << ";" << normalized << "\n";
		}
		CSV.close();
	}
	else if (x == 2){
		std::string path = "C:\\Images\\vertical_histogram";
		path += std::to_string(y);
		path += ".csv";
		CSV.open(path);
		for (int i = 0; i < height; i++)
		{
			float normalized = ((float)csvData[i]);
			CSV << i << ";" << normalized << "\n";
		}
		CSV.close();
	}
}

int* splitLicensePlate::csvHorizontal(){
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			byte whiteOrBlack = image->at(i, j);
			if (whiteOrBlack == 0){
				csvData[i] += 1;
			}
		}
	}
	return csvData;
}

int* splitLicensePlate::csvVertical(){
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			byte whiteOrBlack = image->at(j, i);
			if (whiteOrBlack == 0){
				csvData[i] += 1;
			}
		}
	}
	return csvData;
}