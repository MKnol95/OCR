#include "splitLicensePlate.h"
#include "OCR.h"
#include <corona.h>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include "GlobalDefines.h"
#include <memory.h>

splitLicensePlate::splitLicensePlate()
{
	originalImage = corona::OpenImage((Data::getInstance().getPath() + Data::getInstance().getName()).c_str(), corona::PF_R8G8B8);
	if (!originalImage){
		std::cout << "Failed loading the image :(";
	}
	void* pixels = originalImage->getPixels();
	originalPixels = (byte*)pixels;
	height = originalImage->getHeight();
	width = originalImage->getWidth();
	imageSurface = originalImage->getWidth() * originalImage->getHeight();
	for (int i = 0; i < width; i++){
		splitCSVSplit[i] = 0;
	}
}


splitLicensePlate::~splitLicensePlate()
{
	delete originalImage;
	delete splitImage;
}

int* splitLicensePlate::getSplitCSVSplit()
{
	return  splitCSVSplit;
}

void splitLicensePlate::ProcessImage()
{
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			int xMatrix = (i * 3);
			int yMatrix = (j * (width * 3));
			byte whiteOrBlack = originalPixels[xMatrix + yMatrix];
			if (whiteOrBlack == 0){
				splitCSVSplit[i] += 1;
			}
		}
	}
	int borderLeft[37];
	int borderRight[37];
	int countL = 0, countR = 0;
	for (int i = 0; i < width; i++){
		if (splitCSVSplit[i] != 0 && splitCSVSplit[i - 1] == 0)
		{
			borderLeft[countL] = i;
			countL++;
		}
		else if (splitCSVSplit[i] != 0 && splitCSVSplit[i + 1] == 0)
		{
			borderRight[countR] = i + 1;
			countR++;
		}
	}
	for (int z = 0; z < 37; z++){
		int splitWidth = borderRight[z] - borderLeft[z];
		char buffert[20];
		splitImage = corona::CreateImage(splitWidth, originalImage->getHeight(), corona::PF_R8G8B8);
		if (!splitImage){
			std::cout << "Failed creating the grey image :(";
		}
		void* pixels2 = splitImage->getPixels();
		splitPixels = (byte*)pixels2;
		for (int i = borderLeft[z]; i < borderRight[z]; i++){
			for (int j = 0; j < height; j++){
				for (int k = 0; k < 3; k++)
				{
					//int xSplit = (i*3);
					int xSplit = (i - borderLeft[z]) * 3;
					int ySplit = (j * (splitWidth * 3));
					int xOriginal = (i * 3);
					int yOriginal = (j * (width * 3));
					splitPixels[xSplit + ySplit + k] = originalPixels[xOriginal + yOriginal + k];
				}
			}
		}

		_itoa_s(z, buffert, 20, 10);
		corona::SaveImage((Data::getInstance().getPath() + "split_" + buffert + Data::getInstance().getFile() + ".png").c_str(), corona::FF_PNG, splitImage);
	}
}

void splitLicensePlate::WriteCSV()
{
	splitCSV.open((Data::getInstance().getPath() + "split_" + Data::getInstance().getFile() + "_histogram.csv").c_str());
	for (int i = 0; i < width; i++)
	{
		float normalized = ((float)splitCSVSplit[i]);// / (float)imageSurface);
		splitCSV << i << ";" << normalized << "\n";
	}
	splitCSV.close();
}