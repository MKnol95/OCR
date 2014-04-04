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
	splitLicensePlate::csvVertical();
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
		char buffert[20];

		ImageGray character = ImageGray(splitWidth, image->height());
		/*/splitImage = corona::CreateImage(splitWidth, image->height(), corona::PF_R8G8B8);
		if (!character){
			std::cout << "Failed creating the grey image :(";
		}
		*/
		//void* pixels2 = splitImage->getPixels();
		//splitPixels = (byte*)pixels2;


		for (int i = borderLeft[z]; i < borderRight[z]; i++){
			for (int j = 0; j < height; j++){
				for (int k = 0; k < 3; k++)
				{

					int xSplit = (i - borderLeft[z]);
					//int ySplit = (j * (splitWidth));
					//int xOriginal = i;
					//int yOriginal = j * width;

					unsigned char& pixel = character.at(xSplit, j);
					pixel = image->at(i, j);
					//pixel = image->begin();
				}
			}
		}
		_itoa_s(z, buffert, 20, 10);
		//corona::SaveImage((Data::getInstance().getPath() + "split_" + buffert + Data::getInstance().getFile() + ".png").c_str(), corona::FF_PNG, splitImage);
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
		for (int i = 0; i < width; i++)
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
	for (int i = 0; i < width; i++) {
		splitCSVSplit[i] = 0;
	}
	for (int j = 0; j < height; j++){
		for (int i = 0; i < width; i++){
			byte whiteOrBlack = image->at(i, j);
			if (whiteOrBlack == 0){
				splitCSVSplit[i] += 1;
			}
		}
	}
}