#pragma once
#include <corona.h>
#include "GlobalDefines.h"
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include "imageLib\ImageGray.h"

using namespace ImageLib;

class charChecker
{
private:
	char Char;
	bool horizontal;
	int score[36];
	std::vector<int> csvData;
	int intersectsV = 0, intersectsH = 0, numberPeaksH = 0, numberPeaksV = 0, charWidth = 0;
public:
	charChecker(std::vector<int>&, bool);
	~charChecker();
	char& getChar();
	char process();
	int bucketPeaks(bool);
	int bucketSize();
	int specificationMiddleLine(bool);
};

