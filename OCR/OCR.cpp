#include <vector>
#include <memory>
#include <iostream>
#include "imageLib\ImageLoader.h"
#include "imageLib\ImageRGB.h"
#include "imageLib\ImageGray.h"
#include "charChecker.h"
#include "splitLicensePlate.h"

using namespace ImageLib;

#define NUMBER_OF_CHARACTERS 37
#define HORIZONTAL_HISTOGRAM_SIZE 18
#define VERTICAL_HISTOGRAM_SIZE 15

int main(int argc, char *argv[])
{
	unsigned char compareCharsH[NUMBER_OF_CHARACTERS][HORIZONTAL_HISTOGRAM_SIZE] = { 
		//letters
		{ 0, 4, 4, 4, 6, 6, 5, 6, 6, 5, 6, 6, 10, 12, 12, 5, 6, 6 },
		{ 0, 8, 10, 10, 7, 6, 6, 7, 10, 10, 11, 7, 6, 6, 6, 7, 11, 11 },
		{ 6, 9, 9, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 9, 8 },
		{ 0, 8, 10, 11, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 11, 10 },
		{ 0, 10, 10, 10, 3, 3, 3, 3, 3, 3, 9, 9, 9, 3, 3, 3, 3, 3 },
		{ 5, 8, 9, 6, 3, 3, 3, 3, 3, 3, 9, 9, 9, 5, 6, 7, 11, 10 },
		{ 0, 6, 6, 6, 6, 6, 6, 6, 12, 12, 12, 6, 6, 6, 6, 6, 6, 6 },
		{ 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
		{ 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 8, 7 },
		{ 0, 6, 6, 7, 6, 6, 6, 7, 7, 6, 6, 6, 6, 7, 6, 6, 6, 7 },
		{ 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 10, 10 },
		{ 0, 8, 10, 10, 12, 12, 14, 14, 14, 13, 13, 11, 11, 9, 7, 7, 6, 6 },
		{ 0, 6, 7, 7, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 7, 7 },
		{ 4, 7, 8, 5, 3, 3, 5, 6, 6, 6, 6, 6, 6, 5, 6, 8, 8, 6 },
		{ 0, 8, 9, 10, 7, 6, 6, 6, 7, 8, 7, 6, 3, 3, 3, 3, 3, 3 },
		{ 5, 7, 9, 8, 6, 6, 6, 6, 6, 6, 6, 6, 10, 9, 8, 9, 10, 10 },
		{ 0, 6, 7, 8, 7, 6, 6, 6, 6, 7, 9, 8, 6, 6, 6, 7, 6, 6 },
		{ 5, 8, 9, 6, 3, 3, 3, 4, 5, 6, 5, 4, 3, 3, 4, 7, 11, 9 },
		{ 0, 11, 11, 11, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
		{ 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 10, 8 },
		{ 0, 5, 6, 6, 6, 6, 6, 6, 5, 6, 6, 6, 6, 6, 6, 5, 4, 4 },
		{ 0, 6, 6, 7, 8, 8, 7, 8, 9, 10, 9, 8, 8, 8, 7, 5, 4, 4 },
		{ 0, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 5, 6, 6, 6, 6, 6, 6 },
		{ 0, 6, 6, 6, 6, 6, 6, 6, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3 },
		{ 0, 11, 11, 11, 4, 3, 3, 4, 3, 3, 4, 3, 3, 3, 3, 3, 12, 12 },
		//streepieee
		{ 0, 0, 0, 0, 0, 0, 0, 4, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0 },
		//getallen
		{ 4, 8, 8, 8, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 8, 8, 8 },
		{ 0, 4, 5, 5, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
		{ 5, 8, 9, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 3, 10, 11 },
		{ 6, 9, 9, 6, 3, 3, 3, 3, 5, 5, 6, 4, 3, 3, 4, 7, 10, 8 },
		{ 0, 3, 4, 5, 6, 6, 6, 6, 5, 6, 6, 12, 12, 12, 3, 3, 3, 3 },
		{ 9, 9, 9, 3, 3, 3, 3, 3, 8, 9, 3, 3, 3, 3, 3, 5, 10, 9 },
		{ 3, 3, 3, 3, 3, 3, 3, 7, 9, 10, 7, 6, 6, 6, 6, 6, 10, 8 },
		{ 0, 12, 12, 12, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
		{ 0, 4, 8, 6, 6, 6, 6, 8, 8, 8, 9, 6, 6, 6, 6, 8, 10, 8 },
		{ 4, 8, 10, 6, 6, 6, 6, 6, 6, 6, 10, 9, 6, 3, 2, 2, 3, 3 }
	};

	unsigned char compareCharsV[NUMBER_OF_CHARACTERS][VERTICAL_HISTOGRAM_SIZE] = {
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 }
	};

	for (int R = 0; R < NUMBER_OF_CHARACTERS; R++) {
		for (int C = 0; C < HORIZONTAL_HISTOGRAM_SIZE; C++) {
			compareCharsH[R][C] = 2;
		}
	}
	
	//freeeee
	for (int i = 0; i < NUMBER_OF_CHARACTERS; i++) {
		delete[] compareCharsH[i];
		delete[] compareCharsV[i];
	}
	delete[] compareCharsH;
	delete[] compareCharsV;


	//char test[2] = { 4, 3 };
	// the example kenteken.png has to be in the folder C:\Images
	//Data::getInstance().initializeDefines(argv);
	std::unique_ptr<ImageGray> image(loadImg("C:\\Images\\alle.png"));
	splitLicensePlate* makeSplit = new splitLicensePlate(image);
	std::vector<ImageGray> characters = makeSplit->ProcessImage();
	int number = 0;
	for (ImageGray &character : characters) {
		corona::Image* destination = corona::CreateImage(character.width(), character.height(), corona::PF_R8G8B8);
		unsigned char * pixels = (unsigned char*) destination->getPixels();
		//unsigned char * pixels = new unsigned char[character.width() * character.height() * 3];
		int count = 0;
		for (std::vector<unsigned char>::iterator it = character.begin(); it != character.end(); ++it) {
			pixels[count] = *it;
			pixels[count + 1] = *it;
			pixels[count + 2] = *it;
			count += 3;
		}
		std::string path = "C:\\Images\\test";
		path += std::to_string(number);
		path += ".png";
		corona::SaveImage(path.c_str(), corona::FF_PNG, destination);
		++number;
	}
	makeSplit->WriteCSV(0, 0);
	for (int i = 0; i < 37; i++) {
		std::string path = "C:\\Images\\test";
		path += std::to_string(i);
		path += ".png";
		std::unique_ptr<ImageGray> image(loadImg(path));
		splitLicensePlate* makeh = new splitLicensePlate(image);
		makeh->csvHorizontal();
		makeh->WriteCSV(1,i);
		splitLicensePlate* makev = new splitLicensePlate(image);
		makev->csvVertical();
		makev->WriteCSV(2,i);
	}
	return 0;
}