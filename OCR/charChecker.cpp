#include <corona.h>
#include "GlobalDefines.h"
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include "charChecker.h"

charChecker::charChecker(std::vector<int>& csvDataH, std::vector<int>& csvDataV){
}

charChecker::~charChecker(){
}

char& charChecker::getChar(){
	return  Char;
}

void charChecker::process(){
	bucketSize();


}

int charChecker::bucketPeaks(bool H){
	return numberPeaks;
}

int charChecker::bucketSize(){
	return charWidth;
}

int charChecker::specificationHorizontalMiddleLine(){
	return intersectsH;
}

int charChecker::specificationVerticalMiddleLine(){
	return intersectsV;
}