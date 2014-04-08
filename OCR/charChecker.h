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
	char chars[36] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9'};
	std::vector<int> csvData;
	std::vector<int> csvDataCompareH;
	std::vector<int> csvDataCompareV;
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

