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
public:
	charChecker(std::vector<int>&);
	~charChecker();
	char& charChecker::getChar();
	void charChecker::process();
	void charChecker::bucketPeaks();
	void charChecker::bucketSize();
	void charChecker::specificationHorizontalMidelLine();
	void charChecker::specificationVerticalMidelLine();
};

