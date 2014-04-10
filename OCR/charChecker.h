#pragma once
#include <corona.h>
#include "GlobalDefines.h"
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include "imageLib\ImageGray.h"

using namespace ImageLib;
#define NUMBER_OF_CHARACTERS 37
#define HORIZONTAL_HISTOGRAM_SIZE 30 //15
#define VERTICAL_HISTOGRAM_SIZE 36 //18

class charChecker
{
private:
	char Char;
	bool horizontal;
	int scoreH[NUMBER_OF_CHARACTERS];
	int scoreV[NUMBER_OF_CHARACTERS];
	unsigned short csvDataH[HORIZONTAL_HISTOGRAM_SIZE];
	unsigned short csvDataV[VERTICAL_HISTOGRAM_SIZE];
	int intersectsV = 0, intersectsH = 0, numberPeaksH = 0, numberPeaksV = 0;
	void inter1parray(std::vector<int> a, bool horizontal);
public:
	charChecker(std::vector<int>& csvDataInputH, int height, std::vector<int>& csvDataInputV, bool hor);
	char& getChar();
	char process();
	int bucketPeaks(bool);
	int bucketSize();
	int specificationMiddleLine(bool);
};

