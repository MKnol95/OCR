#pragma once
#include <corona.h>
#include "GlobalDefines.h"
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include "imageLib\ImageGray.h"

using namespace ImageLib;
#define NUMBER_OF_CHARACTERS 36
#define HORIZONTAL_HISTOGRAM_SIZE 19
#define VERTICAL_HISTOGRAM_SIZE 15

class charChecker
{
private:
	char Char;
	bool horizontal;
	int scoreH[36];
	int scoreV[36];
	unsigned char csvDataH[HORIZONTAL_HISTOGRAM_SIZE];
	unsigned char csvDataV[VERTICAL_HISTOGRAM_SIZE];
	int intersectsV = 0, intersectsH = 0, numberPeaksH = 0, numberPeaksV = 0;
	void inter1parray(std::vector<int> a, bool horizontal);
public:
	charChecker(std::vector<int>& csvDataInputH, std::vector<int>& csvDataInputV, bool hor);
	~charChecker();
	char& getChar();
	char process();
	int bucketPeaks(bool);
	int bucketSize();
	int specificationMiddleLine(bool);
};

