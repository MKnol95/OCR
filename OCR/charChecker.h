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
	int intersectsV = 0, intersectsH = 0, numberPeaks = 0, charWidth = 0;
public:
	charChecker(std::vector<int>&);
	~charChecker();
	char& charChecker::getChar();
	void charChecker::process();
	int charChecker::bucketPeaks(bool);
	int charChecker::bucketSize();
	int charChecker::specificationHorizontalMiddleLine();
	int charChecker::specificationVerticalMiddleLine();
};

