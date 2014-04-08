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

	// the example kenteken.png has to be in the folder C:\Images
	//Data::getInstance().initializeDefines(argv);
	std::unique_ptr<ImageGray> image(loadImg("C:\\Images\\kenteken.png"));
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
	for (int i = 0; i < 36; i++) {
		std::string path = "C:\\Images\\test";
		path += std::to_string(i);
		path += ".png";
		std::unique_ptr<ImageGray> image(loadImg(path));
		splitLicensePlate* makeCsv = new splitLicensePlate(image);
		charChecker checker = charChecker(makeCsv->csvHorizontal(),makeCsv->csvVertical(), true);
		char kent = checker.process();
		std::cout << kent;
	}
	int bah;
	std::cin >> bah;
	return 0;
}