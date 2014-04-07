#include "splitLicensePlate.h"
#include <vector>
#include <memory>
#include <vector>
#include "imageLib\ImageLoader.h"
#include "imageLib\ImageRGB.h"
#include "imageLib\ImageGray.h"

using namespace ImageLib;

int main(int argc, char *argv[])
{
	// the example kenteken.png has to be in the folder C:\Images
	Data::getInstance().initializeDefines(argv);
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
		std::string path = "C:\\Images\\";
		path += std::to_string(number);
		path += ".png";
		corona::SaveImage(path.c_str(), corona::FF_PNG, destination);
		++number;
	}
	makeSplit->WriteCSV(0, 0);
	for (int i = 0; i < number; i++) {
		std::string path = "C:\\Images\\";
		path += std::to_string(i);
		path += ".png";
		std::unique_ptr<ImageGray> image(loadImg(path));
		splitLicensePlate* makeCsvHorizontal = new splitLicensePlate(image);
		makeCsvHorizontal->csvHorizontal();
		makeCsvHorizontal->WriteCSV(1,i);
		splitLicensePlate* makeCsvVertical = new splitLicensePlate(image);
		makeCsvVertical->csvVertical();
		makeCsvVertical->WriteCSV(2,i);
	}
	return 0;
}