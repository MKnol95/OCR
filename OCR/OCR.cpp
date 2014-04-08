#include <vector>
#include <memory>
#include <iostream>
#include "imageLib\ImageLoader.h"
#include "imageLib\ImageRGB.h"
#include "imageLib\ImageGray.h"
#include "charChecker.h"
#include "splitLicensePlate.h"

using namespace ImageLib;

int main(int argc, char *argv[])
{
	//char test[2] = { 4, 3 };
	// the example kenteken.png has to be in the folder C:\Images
	//Data::getInstance().initializeDefines(argv);
	std::unique_ptr<ImageGray> image(loadImg("C:\\Images\\genkent.png"));
	splitLicensePlate* makeSplit = new splitLicensePlate(*image);
	std::vector<ImageGray> characters = makeSplit->ProcessImage();
	//save image 
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
	//char recognition starts here
	number = 0;
	for (ImageGray &character : characters) {
		splitLicensePlate* makeCsv = new splitLicensePlate(character);
		charChecker checker = charChecker(makeCsv->csvHorizontal(), character.height(), makeCsv->csvVertical(), true);
		makeCsv->WriteCSV(1, number);
		makeCsv->WriteCSV(2, number);
		char sdgh = checker.process();
		std::cout << number << "\t" << sdgh << std::endl;
		++number;
	}
	int bah;
	std::cin >> bah;
	return 0;
}