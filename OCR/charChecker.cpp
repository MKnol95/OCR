#include <corona.h>
#include "GlobalDefines.h"
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include "charChecker.h"
#include "splitLicensePlate.h"

charChecker::charChecker(std::vector<int>& csvDataInput, bool hor){
	if (hor){
		charChecker::horizontal = true;
	}
	else{
		charChecker::horizontal = false;
	}
	for (int i = 0; i < 36; i++){
		score[i] = 0;
	}	
	charChecker::csvData = csvDataInput;
	charWidth = charChecker::csvData.size();
}

charChecker::~charChecker(){

}

char& charChecker::getChar(){
	return Char;
}

char charChecker::process(){
	for (int j = 0; j < 36; j++){
		// determine score for each character.
		for (int i = 0; i < charWidth; i++){
			if (charChecker::horizontal){
				score[j] += abs(charChecker::csvData[i] - csvDataCompareH[i]);
			}
			else{
				score[j] += abs(charChecker::csvData[i] - csvDataCompareV[i]);
			}
		}
	}
	int min = 99999;
	for (int i = 0; i < 36; i++){
		if (score[i] < min){
			min = i;
		}
	}
	return chars[min];
}
