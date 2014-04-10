#include <vector>
#include <memory>
#include <iostream>
#include "imageLib\ImageLoader.h"
#include "imageLib\ImageRGB.h"
#include "imageLib\ImageGray.h"
#include "CharChecker.h"
#include "SplitLicensePlate.h"
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
				//std::cout << "Start recognition of " << filename << std::endl;
				std::unique_ptr<ImageGray> image(loadImg("C:\\Images\\recognize\\" + filename));
				SplitLicensePlate* makeSplit = new SplitLicensePlate(*image);
				std::vector<ImageGray> characters = makeSplit->ProcessImage();
				//char recognition starts here
				std::string kenteken = matching.RecognizeLicenseplate(characters);
				//std::cout << "LICENSE PLATE: " << kenteken << std::endl;
				delete makeSplit;
				if (antwoord != kenteken) {
					failCount++;
					//std::cout << "MISMATCH" << std::endl;
					Beep(3000, 200);
				}
				else {
					successCount++;
				}
			}
		}
		closedir(pDIR);
	}
	//std::cout << "RESULT: success: " << successCount << " failed: " << failCount << std::endl;
	return 0;
}


