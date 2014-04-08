#include "splitLicensePlate.h"
#include "OCR.h"
#include "imageLib\ImageGray.h"
#include <corona.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "GlobalDefines.h"
#include <memory.h>
#define NORMALIZED_WIDTH 15
#define NORMALIZED_HEIGHT 30

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

std::vector<int>& splitLicensePlate::getCSV()
{
	return  csvData;
}

std::vector<ImageGray> splitLicensePlate::ProcessImage()
{
	std::vector<ImageGray> splitimage;

	const int findArea = 40;/////// 8 karakters + 12 vlekkeen op het kenteken die los van de characters zitten is er mogelijk voor worst case.
	int borderLeft[findArea];
	int borderRight[findArea];
	int countL = 0, countR = 0, areaFound = 0, above = 0, under = 0;
	splitLicensePlate::csvVertical();
	for (int i = 1; i < height; i++){
		if (csvData[i] == 0){
			continue;
		}
		else{
			if (csvData[i - 1] == 0) // vergelijking met de pixel ervoor.
			{
				above = i;
				continue;
			}
			else if(i+1 < height){
				if (csvData[i + 1] == 0){
					under = i;
					break;
				}
			}
		}
	}
	splitLicensePlate::csvHorizontal();
	for (int i = 0; i < width; i++){
		if (csvData[i] == 0) {
			continue;
		}
		if (i == 0) // eerste run
		{
			borderLeft[countL] = i;
			countL++;
		}
		else {
			if (csvData[i - 1] == 0) { // vergelijking met de pixel ervoor.
				borderLeft[countL] = i;
				countL++;
				continue;
			}
			if (i != (width - 1)) { //not last index
				if (csvData[i + 1] == 0) { // vergelijking mer de pixel erna
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

		}
	}
	for (int z = 0; z < areaFound; z++){
		int splitWidth = borderRight[z] - borderLeft[z];
		int splitHeight = under - above;
		ImageGray character = ImageGray(splitWidth, splitHeight);
		for (int i = borderLeft[z]; i < borderRight[z]; i++){
			for (int j = above; j < under; j++){
				int xSplit = (i - borderLeft[z]);
				int ySplit = (j - above);
				unsigned char& pixel = character.at(xSplit, ySplit);
				pixel = image->at(i, j);
			}
		}
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
			int normalized = ((int)csvData[i]);
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
			int normalized = ((int)csvData[i]);
			CSV << i << ";" << normalized << "\n";
		}
		CSV.close();
	}
}

std::vector<int> splitLicensePlate::csvHorizontal(){
	csvData = std::vector<int>(width);
	for (int i = 0; i < width; i++){
		csvData[i] = 0;
	}
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

void splitLicensePlate::csvVertical(){
	csvData = std::vector<int>(height);
	for (int i = 0; i < height; i++){
		csvData[i] = 0;
	}
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			byte whiteOrBlack = image->at(j, i);
			if (whiteOrBlack == 0){
				csvData[i] += 1;
			}
		}
	}
}
