#include "splitLicensePlate.h"
#include "OCR.h"
#include "imageLib\ImageGray.h"
#include <corona.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include "GlobalDefines.h"
#include <memory.h>
#define NORMALIZED_WIDTH 15
#define NORMALIZED_HEIGHT 30

using namespace ImageLib;

splitLicensePlate::splitLicensePlate(ImageGray& img) : image(img)
{
	//image = std::move(img);
	width = img.width();
	height = img.height();
	imageSurface = width * height;
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
		if (csvDataV[i] == 0){
			continue;
		}
		else{
			if (csvDataV[i - 1] == 0) // vergelijking met de pixel ervoor.
			{
				above = i;
				continue;
			}
			else if(i+1 < height){
				if (csvDataV[i + 1] == 0){
					under = i;
					break;
				}
			}
		}
	}
	splitLicensePlate::csvHorizontal();
	for (int i = 0; i < width; i++){
		if (csvDataH[i] == 0) {
			continue;
		}
		if (i == 0) // eerste run
		{
			borderLeft[countL] = i;
			countL++;
		}
		else {
			if (csvDataH[i - 1] == 0) { // vergelijking met de pixel ervoor.
				borderLeft[countL] = i;
				countL++;
				continue;
			}
			if (i != (width - 1)) { //not last index
				if (csvDataH[i + 1] == 0) { // vergelijking mer de pixel erna
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
		int shiftUp = 0;
		int shiftHeight = under;
		//slice more white spaces in top and bottom of the character
		for (int j = above; j < under; j++){
			bool blackFound = false;
			for (int i = borderLeft[z]; i < borderRight[z]; i++){
				blackFound = image.at(i, j) == 0 ? true : false;
				if (blackFound) 
					break;
			}
			if (blackFound)
			{
				if (shiftUp == 0)
					shiftUp = j - above;
			}
			else {
				if (shiftUp != 0) {	
					//black was already found at least one time. Now only white detected. This means we found white under the char
					shiftHeight = j;
					break;
				}
			}
		}
		//slicing corrected
		ImageGray character = ImageGray(splitWidth, (shiftHeight - above - shiftUp));
		for (int j = (above + shiftUp); j < shiftHeight; j++){
			for (int i = borderLeft[z]; i < borderRight[z]; i++){
				int xSplit = (i - borderLeft[z]);
				int ySplit = (j - (above + shiftUp));
				unsigned char& pixel = character.at(xSplit, ySplit);
				pixel = image.at(i, j);
			}
		}
		splitimage.push_back(character);
	}
	return splitimage;
}

void splitLicensePlate::WriteCSV(int x, int y)
{
	std::ofstream CSVWriter;
	if (x == 0 && y == 0){
		std::string path = "C:\\Images\\Split_Histogram.csv";
		CSVWriter.open(path);
		for (int i = 0; i < width; i++)
		{
			int normalized = ((int)csvDataH[i]);
			CSVWriter << i << ";" << normalized << "\n";
		}
		CSVWriter.close();
	}
	else if (x == 1){
		std::string path = "C:\\Images\\horizontal_histogram";
		path += std::to_string(y);
		path += ".csv";
		CSVWriter.open(path);
		for (int i = 0; i < width; i++)
		{
			float normalized = ((float)csvDataH[i]);
			CSVWriter << i << ";" << normalized << "\n";
		}
		CSVWriter.close();
	}
	else if (x == 2){
		std::string path = "C:\\Images\\vertical_histogram";
		path += std::to_string(y);
		path += ".csv";
		CSVWriter.open(path);
		for (int i = 0; i < height; i++)
		{
			float normalized = ((float)csvDataV[i]);
			CSVWriter << i << ";" << normalized << "\n";
		}
		CSVWriter.close();
	}
}

std::vector<int> splitLicensePlate::csvHorizontal(){
	csvDataH = std::vector<int>(width);
	for (int i = 0; i < width; i++){
		csvDataH[i] = 0;
	}
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			byte whiteOrBlack = image.at(i, j);
			if (whiteOrBlack == 0){
				csvDataH[i] += 1;
			}
		}
	}
	return csvDataH;
}

std::vector<int> splitLicensePlate::csvVertical(){
	csvDataV = std::vector<int>(height);
	for (int i = 0; i < height; i++){
		csvDataV[i] = 0;
	}
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			byte whiteOrBlack = image.at(j, i);
			if (whiteOrBlack == 0){
				csvDataV[i] += 1;
			}
		}
	}
	return csvDataV;
}
