#include <vector>
#include <memory>
#include <iostream>
#include "imageLib\ImageLoader.h"
#include "imageLib\ImageRGB.h"
#include "imageLib\ImageGray.h"
#include "charChecker.h"
#include "splitLicensePlate.h"
#include "OCRPatternMatching.h"
#include <Windows.h>
#include <WinBase.h>

#include <cstdlib>
#include "dirent.h"
#if DEBUG
	#include <vld.h>
#endif

using namespace ImageLib;



int main(short argc, char *argv[])
{
	/*
	font creator
	std::unique_ptr<ImageGray> image(loadImg("C:\\Images\\alle.png"));
	splitLicensePlate* makeSplit = new splitLicensePlate(*image);
	std::vector<ImageGray> characters = makeSplit->ProcessImage();
	//save image 
	int number = 0;
	for (ImageGray &character : characters) {
		corona::Image* destination = corona::CreateImage(character.width(), character.height(), corona::PF_R8G8B8);
		unsigned char * pixels = (unsigned char*)destination->getPixels();
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
	*/
	unsigned short successCount = 0;
	unsigned short failCount = 0;
	DIR *pDIR;
	struct dirent *entry;
	if (pDIR = opendir("C:\\Images\\recognize\\")){
		OCRPatternMatching matching;
		while (entry = readdir(pDIR)){
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
				std::string filename = entry->d_name;
				if (filename.substr(filename.length() - 4, 4) != ".png")
					continue;
				std::string antwoord = filename.substr(0, 8);
				std::cout << "Start recognition of " << filename << std::endl;
				std::unique_ptr<ImageGray> image(loadImg("C:\\Images\\recognize\\" + filename));
				splitLicensePlate* makeSplit = new splitLicensePlate(*image);
				std::vector<ImageGray> characters = makeSplit->ProcessImage();
				//save image 
				//unsigned char number = 0;
				/*for (ImageGray &character : characters) {
					corona::Image* destination = corona::CreateImage(character.width(), character.height(), corona::PF_R8G8B8);
					unsigned char * pixels = (unsigned char*)destination->getPixels();
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
				*/
				//char recognition starts here

				std::string kenteken = matching.RecognizeLicenseplate(characters);
				/*number = 0;
				for (ImageGray &character : characters) {
					char yolo = matching.Recognize(character);

					
					splitLicensePlate* makeCsv = new splitLicensePlate(character);
					charChecker checker = charChecker(makeCsv->csvHorizontal(), character.height(), makeCsv->csvVertical(), true);
					makeCsv->WriteCSV(1, number);
					makeCsv->WriteCSV(2, number);
					char sdgh = checker.process();
					if (number == 0 && yolo == '-'){
						std::cout << std::endl;
						continue;
					}
					else if (number > 7 && yolo == '-'){
						std::cout << std::endl;
						break;
					}
					kenteken += yolo;
					std::cout << yolo << std::endl;
					++number;
				}*/
				std::cout << "LICENSE PLATE: " << kenteken << std::endl;
				delete makeSplit;
				if (antwoord != kenteken) {
					failCount++;
					std::cout << "MISMATCH" << std::endl;
					Beep(3000, 200);
				}
				else {
					successCount++;
				}
			}
		}
		closedir(pDIR);
	}
	std::cout << "RESULT: success: " << successCount << " failed: " << failCount << std::endl;
	char bah;
	std::cin >> bah;
	return 0;
}


