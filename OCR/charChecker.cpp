#include <corona.h>
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include "CharChecker.h"
#include "SplitLicensePlate.h"
#include <iostream>

unsigned char compareCharsH[NUMBER_OF_CHARACTERS][HORIZONTAL_HISTOGRAM_SIZE] = {
	{ 2, 3, 4, 6, 7, 8, 8, 9, 10, 11, 11, 11, 10, 9, 8, 8, 8, 9, 11, 11, 11, 9, 8, 8, 8, 7, 6, 4, 3, 2 },
	{ 17, 17, 17, 17, 17, 17, 14, 11, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 10, 11, 12, 14, 15, 15, 14, 12, 10, 7, 5 },
	{ 8, 9, 11, 13, 14, 15, 15, 13, 10, 8, 8, 7, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 4 },
	{ 17, 17, 17, 17, 17, 16, 11, 6, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 7, 8, 10, 12, 13, 12, 10, 9, 7, 6 },
	{ 17, 17, 17, 17, 17, 17, 17, 15, 12, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 6, 5, 5 },
	{ 17, 17, 17, 17, 17, 17, 17, 15, 11, 8, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 4, 3, 3 },
	{ 7, 9, 11, 13, 14, 14, 12, 9, 8, 6, 5, 5, 5, 5, 5, 5, 6, 8, 8, 8, 8, 8, 9, 10, 10, 9, 8, 8, 8, 8 },
	{ 17, 17, 17, 17, 17, 17, 13, 7, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 13, 17, 17, 17, 17, 17, 17 },
	{ 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17 },
	{ 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 10, 14, 16, 16, 16, 16, 15, 15, 15, 15 },
	{ 17, 17, 17, 17, 17, 17, 13, 8, 4, 4, 4, 5, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 7, 6, 5, 4, 3, 2, 1, 1 },
	{ 17, 17, 17, 17, 17, 17, 17, 14, 9, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 17, 17, 17, 17, 14, 9, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 9, 14, 17, 17, 17, 17 },
	{ 17, 17, 17, 17, 17, 17, 13, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 13, 17, 17, 17, 17, 17, 17 },
	{ 7, 8, 9, 10, 11, 11, 10, 8, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 6, 7, 8, 9, 11, 13, 14, 14, 13, 11, 9, 7 },
	{ 17, 17, 17, 17, 17, 17, 16, 11, 6, 3, 3, 3, 3, 4, 5, 6, 6, 6, 6, 7, 7, 8, 8, 8, 8, 7, 7, 6, 5, 5 },
	{ 9, 10, 12, 13, 14, 14, 11, 8, 7, 7, 6, 6, 6, 6, 6, 7, 8, 9, 9, 9, 9, 9, 9, 12, 15, 15, 15, 13, 11, 9 },
	{ 17, 17, 17, 17, 17, 17, 12, 7, 2, 2, 2, 3, 5, 6, 7, 9, 10, 10, 10, 11, 12, 12, 11, 10, 9, 8, 6, 4, 2, 0 },
	{ 7, 7, 8, 9, 10, 10, 10, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 10, 10, 8, 6, 5, 4, 4 },
	{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 9, 14, 17, 17, 17, 17, 17, 17, 14, 9, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 14, 14, 15, 16, 16, 16, 13, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7, 13, 16, 16, 16, 15, 14, 14 },
	{ 4, 5, 6, 7, 9, 10, 10, 10, 9, 9, 9, 8, 7, 6, 6, 6, 6, 7, 8, 9, 10, 10, 10, 10, 9, 9, 8, 7, 5, 4 },
	{ 5, 6, 8, 10, 11, 11, 11, 10, 9, 10, 12, 13, 13, 13, 13, 13, 13, 12, 11, 10, 10, 10, 10, 11, 11, 10, 9, 7, 5, 4 },
	{ 2, 3, 5, 6, 8, 9, 10, 11, 11, 11, 11, 10, 8, 7, 7, 7, 7, 8, 10, 11, 11, 11, 10, 10, 9, 8, 6, 5, 3, 2 },
	{ 1, 1, 2, 3, 4, 5, 5, 5, 6, 6, 6, 9, 11, 11, 10, 10, 11, 11, 9, 6, 6, 6, 5, 5, 5, 4, 3, 2, 1, 1 },
	{ 2, 3, 5, 6, 7, 7, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 9, 9, 8, 8, 7, 6, 6, 6 },
	{ 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1 },
	{ 9, 10, 12, 13, 15, 16, 14, 11, 7, 7, 7, 6, 5, 5, 5, 5, 5, 5, 6, 7, 7, 7, 11, 14, 16, 15, 13, 12, 10, 9 },
	{ 3, 3, 3, 3, 3, 3, 3, 3, 4, 6, 8, 10, 12, 14, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17 },
	{ 1, 2, 3, 5, 5, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 10, 10, 11, 11, 11, 10, 9, 9, 8, 7, 6 },
	{ 6, 6, 6, 6, 6, 6, 6, 6, 7, 8, 8, 8, 8, 8, 8, 8, 9, 10, 11, 12, 13, 14, 14, 14, 13, 11, 10, 8, 6, 4 },
	{ 4, 4, 4, 5, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 11, 15, 17, 17, 17, 17, 17, 15, 10, 4, 3, 3, 3 },
	{ 13, 13, 13, 12, 12, 12, 11, 9, 8, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 9, 10, 11, 10, 8, 7, 6, 5, 4 },
	{ 5, 6, 8, 10, 11, 12, 12, 11, 10, 10, 10, 9, 9, 9, 9, 9, 8, 8, 7, 7, 7, 7, 8, 9, 9, 9, 8, 7, 5, 4 },
	{ 3, 3, 3, 3, 3, 3, 4, 5, 6, 6, 7, 8, 8, 8, 9, 9, 10, 10, 10, 10, 10, 10, 8, 7, 6, 6, 5, 4, 3, 3 },
	{ 4, 6, 8, 10, 13, 15, 15, 14, 12, 11, 9, 8, 7, 7, 7, 7, 7, 7, 8, 9, 11, 12, 14, 15, 15, 13, 11, 9, 6, 4 },
	{ 5, 6, 8, 9, 10, 10, 9, 7, 6, 6, 6, 7, 7, 7, 8, 8, 9, 9, 9, 9, 9, 9, 10, 11, 12, 11, 10, 8, 6, 5 }
};
	
unsigned char compareCharsV[NUMBER_OF_CHARACTERS][VERTICAL_HISTOGRAM_SIZE] = {
	{ 0, 1, 3, 4, 4, 4, 4, 4, 5, 6, 6, 5, 5, 5, 5, 6, 6, 5, 5, 5, 5, 6, 6, 6, 8, 10, 11, 12, 12, 11, 8, 5, 5, 6, 6, 6 },
	{ 0, 3, 7, 8, 9, 10, 10, 8, 7, 6, 6, 6, 6, 6, 6, 7, 9, 10, 10, 10, 10, 10, 8, 6, 6, 6, 6, 6, 6, 6, 6, 7, 9, 11, 11, 11 },
	{ 6, 7, 8, 9, 9, 7, 5, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 6, 8, 8, 8 },
	{ 0, 3, 7, 8, 9, 10, 10, 9, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 9, 10, 10, 10 },
	{ 0, 4, 9, 10, 10, 10, 10, 7, 3, 3, 3, 3, 3, 4, 7, 9, 9, 9, 9, 7, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 10, 10, 10 },
	{ 0, 4, 9, 10, 10, 10, 10, 7, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 7, 9, 9, 9, 9, 8, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 5, 6, 7, 8, 8, 7, 6, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 7, 9, 9, 9, 9, 8, 6, 5, 5, 6, 6, 7, 9, 10, 10, 10 },
	{ 0, 2, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 10, 12, 12, 12, 12, 10, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
	{ 0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 5, 6, 7, 7, 7 },
	{ 0, 2, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7 },
	{ 0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 10, 10, 10 },
	{ 0, 3, 7, 8, 9, 10, 10, 10, 11, 12, 12, 12, 13, 14, 14, 14, 14, 13, 13, 13, 13, 12, 11, 11, 11, 10, 9, 8, 7, 7, 7, 6, 6, 6, 6, 6 },
	{ 0, 2, 5, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 7, 7, 7, 7, 7 },
	{ 4, 5, 6, 7, 7, 6, 5, 4, 3, 3, 3, 3, 4, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 6, 7, 8, 8, 7, 6, 6 },
	{ 0, 3, 7, 8, 8, 9, 9, 8, 7, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 6, 6, 5, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 5, 5, 6, 7, 8, 8, 8, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 8, 9, 9, 8, 8, 8, 8, 9, 9, 10, 10, 10 },
	{ 0, 2, 5, 6, 6, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 8, 8, 8, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
	{ 5, 6, 7, 8, 8, 7, 6, 4, 3, 3, 3, 3, 3, 3, 3, 4, 4, 5, 5, 5, 5, 4, 4, 3, 3, 3, 3, 3, 3, 4, 5, 7, 9, 10, 9, 9 },
	{ 0, 5, 10, 11, 11, 11, 11, 7, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 0, 2, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 8, 9, 8, 8 },
	{ 0, 2, 4, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 4, 4, 4, 4, 4 },
	{ 0, 2, 5, 6, 6, 6, 6, 7, 7, 8, 8, 7, 7, 7, 7, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 7, 7, 6, 5, 4, 4, 4, 4, 4 },
	{ 0, 2, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 4, 4, 4, 4, 4, 4, 4, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
	{ 0, 2, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 0, 5, 10, 11, 11, 11, 11, 8, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 12, 12, 12 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 4, 5, 5, 4, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 4, 5, 7, 8, 8, 8, 8, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 8, 8, 8, 8, 8 },
	{ 0, 1, 3, 4, 4, 5, 5, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 5, 6, 7, 8, 8, 7, 6, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 10, 10, 11 },
	{ 6, 7, 8, 9, 9, 7, 6, 4, 3, 3, 3, 3, 3, 3, 3, 3, 4, 5, 5, 5, 5, 5, 4, 3, 3, 3, 3, 3, 3, 4, 5, 7, 8, 9, 8, 8 },
	{ 0, 1, 2, 3, 3, 4, 4, 5, 5, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 6, 6, 7, 10, 12, 12, 12, 12, 10, 6, 3, 3, 3, 3, 3, 3, 3 },
	{ 9, 9, 9, 9, 9, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 6, 8, 8, 7, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 5, 7, 9, 9, 9 },
	{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 6, 7, 8, 9, 9, 9, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 8, 9, 8, 8 },
	{ 0, 5, 11, 12, 12, 12, 12, 8, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 0, 1, 3, 5, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 7, 8, 8, 8, 8, 8, 8, 8, 6, 6, 6, 6, 6, 6, 6, 6, 7, 8, 9, 9, 8, 8 },
	{ 4, 5, 7, 8, 9, 8, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 8, 9, 9, 8, 7, 5, 4, 2, 2, 2, 2, 2, 2, 3, 3, 3 }
};

CharChecker::CharChecker(std::vector<int>& csvDataInputH, int height, std::vector<int>& csvDataInputV, bool hor){
	if (hor){
		CharChecker::horizontal = true;
	}
	else{
		CharChecker::horizontal = false;
	}
	for (int i = 0; i < NUMBER_OF_CHARACTERS; i++){
		scoreH[i] = 0;
		scoreV[i] = 0;
	}	

	inter1parray(csvDataInputH, true);
	inter1parray(csvDataInputV, false);

	float dimension = (float)(height / VERTICAL_HISTOGRAM_SIZE);
	if (dimension > 1) {
		for (int i = 0; i < NUMBER_OF_CHARACTERS; i++) {
			csvDataH[i] = (unsigned short)(csvDataH[i] / dimension);
			csvDataV[i] = (unsigned short)(csvDataV[i] / dimension);
		}
	}

}

char& CharChecker::getChar(){
	return Char;
}

// linear interpolate x in an array
// inline
int interp1(float x, std::vector<int>& a, int n)
{
	if (x <= 0)  return a[0];
	if (x >= n - 1)  return a[n - 1];
	int j = int(x);
	return (int)(a[j] + (x - j) * (a[j + 1] - a[j]));
}

// linear interpolate array a[] -> array b[]
void CharChecker::inter1parray(std::vector<int> a, bool horizontal)
{
	int n = a.size();
	int m = horizontal ? HORIZONTAL_HISTOGRAM_SIZE : VERTICAL_HISTOGRAM_SIZE;
	float step = float(n - 1) / (m - 1);
	for (int j = 0; j < m; j++){
		if (horizontal)
			csvDataH[j] = interp1(j*step, a, n);
		else
			csvDataV[j] = interp1(j*step, a, n);
	}
}

char CharChecker::process(){
	for (int j = 0; j < NUMBER_OF_CHARACTERS; j++){
		// determine score for each character.
		for (int i = 0; i < HORIZONTAL_HISTOGRAM_SIZE; i++){
			scoreH[j] += abs(CharChecker::csvDataH[i] - compareCharsH[j][i]);
		}
		for (int i = 0; i < VERTICAL_HISTOGRAM_SIZE; i++){
			scoreV[j] += abs(CharChecker::csvDataV[i] - compareCharsV[j][i]);
		}
	}
	int tempValue = 99999;
	int hor = 0;
	for (int i = 0; i < NUMBER_OF_CHARACTERS; i++){
		if (scoreH[i] < tempValue){
			tempValue = scoreH[i];
			hor = i;
		}
	}
	tempValue = 99999;
	int ver = 0;
	for (int i = 0; i < NUMBER_OF_CHARACTERS; i++){
		if (scoreV[i] < tempValue){
			tempValue = scoreV[i];
			ver = i;
		}
	}
	int min = 0;
	if (scoreH[hor] < scoreV[ver]){
		min = hor;
	}
	else{
		min = ver;
	}
	
	if (min < 26) {
		//letter
		min += 65;
	}
	else if (min == 26) {
		min += 19; //-
	}
	else {
		//number
		min += 21;
	}
	Char = min & 0xff;
	return Char;//chars[min];
}
