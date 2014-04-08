#include <corona.h>
#include "GlobalDefines.h"
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include "charChecker.h"
#include "splitLicensePlate.h"
#include <iostream>


//char chars[36] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
//std::vector<int> csvDataCompareH = {0,3,5,7,8,8,8,8,7,7,7,5,4,2,0};
//std::vector<int> csvDataCompareV = { 1, 2, 5, 7, 8, 8, 8, 8, 7, 7, 7, 5, 4, 2, 0 };
unsigned char compareCharsH[NUMBER_OF_CHARACTERS][HORIZONTAL_HISTOGRAM_SIZE] = {
	{ 2, 4, 7, 8, 10, 11, 10, 8, 9, 11, 10, 8, 7, 4, 2 },			//a
	{ 17, 17, 17, 13, 8, 8, 8, 8, 8, 10, 12, 14, 14, 10, 5 },		//b
	{ 8, 11, 14, 15, 10, 7, 6, 5, 5, 5, 5, 5, 5, 5, 4 },			//c
	{ 17, 17, 17, 10, 5, 5, 5, 5, 6, 6, 8, 11, 12, 9, 6 },			//d
	{ 17, 17, 17, 17, 11, 8, 8, 8, 8, 8, 8, 8, 8, 6, 5 },			//e
	{ 17, 17, 17, 17, 10, 6, 6, 6, 6, 6, 6, 6, 6, 4, 3 },			//f
	{ 7, 12, 14, 11, 7, 5, 5, 5, 7, 8, 8, 9, 10, 8, 8 },			//g
	{ 17, 17, 17, 11, 3, 3, 3, 3, 3, 3, 3, 11, 17, 17, 17 },		//h
	{ 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17 }, //i
	{ 3, 2, 2, 2, 2, 2, 2, 2, 2, 5, 13, 16, 16, 15, 15 },			//j
	{ 17, 17, 17, 12, 4, 4, 7, 9, 9, 9, 9, 7, 4, 2, 1 },			//k
	{ 17, 17, 17, 17, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },			//l
	{ 17, 17, 14, 7, 7, 7, 6, 7, 6, 7, 7, 7, 14, 17, 17 },			//m
	{ 17, 17, 17, 13, 6, 6, 6, 6, 6, 6, 6, 13, 17, 17, 17 },		//n
	{ 7, 9, 11, 10, 6, 6, 5, 5, 5, 7, 9, 13, 14, 11, 7 },			//o
	{ 17, 17, 17, 15, 4, 3, 3, 6, 6, 6, 8, 8, 7, 6, 5 },			//p
	{ 9, 12, 14, 11, 7, 6, 6, 7, 8, 9, 9, 12, 15, 14, 9 },			//q
	{ 17, 17, 17, 11, 2, 2, 5, 8, 10, 11, 12, 11, 8, 4, 0 },		//r
	{ 7, 8, 10, 10, 8, 8, 8, 8, 8, 8, 8, 10, 8, 5, 4 },				//s
	{ 3, 3, 3, 3, 3, 11, 17, 17, 17, 10, 3, 3, 3, 3, 3 },			//t
	{ 14, 15, 16, 11, 2, 2, 2, 2, 2, 2, 2, 11, 16, 15, 14 },		//u
	{ 4, 6, 9, 10, 9, 9, 6, 6, 6, 9, 10, 10, 9, 7, 4 },				//v
	{ 5, 8, 11, 10, 9, 12, 13, 13, 13, 10, 10, 11, 10, 7, 4 },		//w
	{ 2, 5, 8, 10, 11, 11, 8, 7, 8, 11, 11, 10, 8, 5, 2 },			//x
	{ 1, 2, 4, 5, 6, 7, 11, 10, 11, 7, 6, 5, 4, 2, 1 },				//y
	{ 2, 5, 7, 8, 9, 9, 9, 9, 10, 10, 10, 9, 8, 6, 6 },				//z
	{ 1, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 1 },				//-
	{ 9, 12, 15, 13, 7, 7, 5, 5, 5, 7, 7, 13, 15, 12, 9 },			//0
	{ 3, 3, 3, 3, 5, 9, 13, 17, 17, 17, 17, 17, 17, 17, 17 },		//1
	{ 1, 3, 5, 7, 7, 8, 9, 10, 9, 9, 11, 11, 9, 8, 6 },
	{ 6, 6, 6, 6, 7, 8, 8, 8, 10, 12, 14, 14, 12, 8, 4 },
	{ 4, 4, 6, 7, 7, 7, 7, 7, 9, 17, 17, 17, 10, 3, 3 },
	{ 13, 13, 12, 11, 7, 7, 7, 7, 7, 7, 9, 11, 9, 6, 4 },
	{ 5, 8, 11, 11, 10, 10, 9, 9, 8, 7, 7, 8, 9, 7, 4 },
	{ 3, 3, 3, 4, 6, 7, 8, 9, 10, 10, 10, 8, 6, 4, 3 },
	{ 4, 8, 13, 14, 12, 9, 7, 7, 7, 9, 12, 14, 13, 9, 4 },
	{ 5, 8, 10, 9, 6, 6, 7, 8, 9, 9, 9, 11, 11, 8, 5 }				//9
};
	
unsigned char compareCharsV[NUMBER_OF_CHARACTERS][VERTICAL_HISTOGRAM_SIZE] = {
	//letters
	{ 0, 4, 4, 4, 6, 6, 5, 6, 6, 5, 6, 6, 10, 12, 12, 5, 6, 6 },
	{ 0, 8, 10, 10, 7, 6, 6, 7, 10, 10, 11, 7, 6, 6, 6, 7, 11, 11 },
	{ 6, 9, 9, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 9, 8 },
	{ 0, 8, 10, 11, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 11, 10 },
	{ 0, 10, 10, 10, 3, 3, 3, 9, 9, 9, 3, 3, 3, 3, 3, 3, 10, 10 },
	{ 0, 10, 10, 10, 3, 3, 3, 3, 3, 3, 9, 9, 9, 3, 3, 3, 3, 3 },
	{ 5, 8, 9, 6, 3, 3, 3, 3, 3, 3, 9, 9, 9, 5, 6, 7, 11, 10 },
	{ 0, 6, 6, 6, 6, 6, 6, 6, 12, 12, 12, 6, 6, 6, 6, 6, 6, 6 },
	{ 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 8, 7 },
	{ 0, 6, 6, 7, 6, 6, 6, 7, 7, 6, 6, 6, 6, 7, 6, 6, 6, 7 },
	{ 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 10, 10 },
	{ 0, 8, 10, 10, 12, 12, 14, 14, 14, 13, 13, 11, 11, 9, 7, 7, 6, 6 },
	{ 0, 6, 7, 7, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 7, 7 },
	{ 4, 7, 8, 5, 3, 3, 5, 6, 6, 6, 6, 6, 6, 5, 6, 8, 8, 6 },
	{ 0, 8, 9, 10, 7, 6, 6, 6, 7, 8, 7, 6, 3, 3, 3, 3, 3, 3 },
	{ 5, 7, 9, 8, 6, 6, 6, 6, 6, 6, 6, 6, 10, 9, 8, 9, 10, 10 },
	{ 0, 6, 7, 8, 7, 6, 6, 6, 6, 7, 9, 8, 6, 6, 6, 7, 6, 6 },
	{ 5, 8, 9, 6, 3, 3, 3, 4, 5, 6, 5, 4, 3, 3, 4, 7, 11, 9 },
	{ 0, 11, 11, 11, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 10, 8 },
	{ 0, 5, 6, 6, 6, 6, 6, 6, 5, 6, 6, 6, 6, 6, 6, 5, 4, 4 },
	{ 0, 6, 6, 7, 8, 8, 7, 8, 9, 10, 9, 8, 8, 8, 7, 5, 4, 4 },
	{ 0, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 5, 6, 6, 6, 6, 6, 6 },
	{ 0, 6, 6, 6, 6, 6, 6, 6, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 0, 11, 11, 11, 4, 3, 3, 4, 3, 3, 4, 3, 3, 3, 3, 3, 12, 12 },
	//streepieee
	{ 0, 0, 0, 0, 0, 0, 0, 4, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0 },
	//getallen
	{ 4, 8, 8, 8, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 8, 8, 8 },
	{ 0, 4, 5, 5, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 5, 8, 9, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 3, 10, 11 },
	{ 6, 9, 9, 6, 3, 3, 3, 3, 5, 5, 6, 4, 3, 3, 4, 7, 10, 8 },
	{ 0, 3, 4, 5, 6, 6, 6, 6, 5, 6, 6, 12, 12, 12, 3, 3, 3, 3 },
	{ 9, 9, 9, 3, 3, 3, 3, 3, 8, 9, 3, 3, 3, 3, 3, 5, 10, 9 },
	{ 3, 3, 3, 3, 3, 3, 3, 7, 9, 10, 7, 6, 6, 6, 6, 6, 10, 8 },
	{ 0, 12, 12, 12, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 0, 4, 8, 6, 6, 6, 6, 8, 8, 8, 9, 6, 6, 6, 6, 8, 10, 8 },
	{ 4, 8, 10, 6, 6, 6, 6, 6, 6, 6, 10, 9, 6, 3, 2, 2, 3, 3 }
	
};


/*
for (int R = 0; R < NUMBER_OF_CHARACTERS; R++) {
	for (int C = 0; C < HORIZONTAL_HISTOGRAM_SIZE; C++) {
		compareCharsH[R][C] = 2;
	}
}

//freeeee
for (int i = 0; i < NUMBER_OF_CHARACTERS; i++) {
	delete[] compareCharsH[i];
	delete[] compareCharsV[i];
}
delete[] compareCharsH;
delete[] compareCharsV;
*/

charChecker::charChecker(std::vector<int>& csvDataInputH, int height, std::vector<int>& csvDataInputV, bool hor){
	if (hor){
		charChecker::horizontal = true;
	}
	else{
		charChecker::horizontal = false;
	}
	for (int i = 0; i < NUMBER_OF_CHARACTERS; i++){
		scoreH[i] = 0;
		scoreV[i] = 0;
	}	

	inter1parray(csvDataInputH, true);
	inter1parray(csvDataInputV, false);

	float dimension = height / VERTICAL_HISTOGRAM_SIZE;
	if (dimension > 1) {
		for (int i = 0; i < NUMBER_OF_CHARACTERS; i++) {
			csvDataH[i] = csvDataH[i] / dimension;
			csvDataV[i] = csvDataV[i] / dimension;
		}
	}

	/*/ik ben marco
	std::cout << "{";
	for (int i = 0; i < HORIZONTAL_HISTOGRAM_SIZE; i++) {
		std::cout << (int)(csvDataH[i]) << (i == HORIZONTAL_HISTOGRAM_SIZE - 1 ? " " : ", ");
	}
	std::cout << "}," << std::endl;*/
}

char& charChecker::getChar(){
	return Char;
}

// linear interpolate x in an array
// inline
int interp1(float x, std::vector<int>& a, int n)
{
	if (x <= 0)  return a[0];
	if (x >= n - 1)  return a[n - 1];
	int j = int(x);
	return a[j] + (x - j) * (a[j + 1] - a[j]);
}

// linear interpolate array a[] -> array b[]
void charChecker::inter1parray(std::vector<int> a, bool horizontal)
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

char charChecker::process(){
	for (int j = 0; j < NUMBER_OF_CHARACTERS; j++){
		// determine score for each character.
		for (int i = 0; i < HORIZONTAL_HISTOGRAM_SIZE; i++){
			scoreH[j] += abs(charChecker::csvDataH[i] - compareCharsH[j][i]);
		}
		for (int i = 0; i < VERTICAL_HISTOGRAM_SIZE; i++){
			scoreV[j] += abs(charChecker::csvDataV[i] - compareCharsV[j][i]);
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
	return (min & 0xff);//chars[min];
}
