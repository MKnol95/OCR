#include <corona.h>
#include "GlobalDefines.h"
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include "charChecker.h"
#include "splitLicensePlate.h"

//char chars[36] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
std::vector<int> csvDataCompareH = {0,3,5,7,8,8,8,8,7,7,7,5,4,2,0};
std::vector<int> csvDataCompareV = { 1, 2, 5, 7, 8, 8, 8, 8, 7, 7, 7, 5, 4, 2, 0 };

charChecker::charChecker(std::vector<int>& csvDataInputH, std::vector<int>& csvDataInputV, bool hor){
	if (hor){
		charChecker::horizontal = true;
	}
	else{
		charChecker::horizontal = false;
	}
	for (int i = 0; i < 36; i++){
		scoreH[i] = 0;
		scoreV[i] = 0;
	}	
	charChecker::csvDataH = csvDataInputH;
	charChecker::csvDataV = csvDataInputV;
	charWidthH = charChecker::csvDataH.size();
	charWidthV = charChecker::csvDataH.size();
}

charChecker::~charChecker(){

}

char& charChecker::getChar(){
	return Char;
}

// linear interpolate x in an array
// inline
int interp1(int x, std::vector<int> a, int n)
{
	if (x <= 0)  return a[0];
	if (x >= n - 1)  return a[n - 1];
	int j = int(x);
	return a[j] + (x - j) * (a[j + 1] - a[j]);
}

// linear interpolate array a[] -> array b[]
void inter1parray(std::vector<int> a, int n, std::vector<int> b, int m)
{
	int step = int(n - 1) / (m - 1);
	for (int j = 0; j < m; j++){
		b[j] = interp1(j*step, a, n);
	}
}

char charChecker::process(){
	inter1parray(csvDataH, charWidthH, csvDataCompareH, csvDataCompareH.size());
	for (int j = 0; j < 36; j++){
		// determine score for each character.
		for (int i = 0; i < charWidthH; i++){
			scoreH[j] += abs(charChecker::csvDataH[i] - csvDataCompareH[i]);
		}
		for (int i = 0; i < charWidthV; i++){
			scoreV[j] += abs(charChecker::csvDataV[i] - csvDataCompareV[i]);
		}
	}
	int hor = 99999;
	for (int i = 0; i < 36; i++){
		if (scoreH[i] < hor){
			hor = i;
		}
	}
	int ver = 99999;
	for (int i = 0; i < 36; i++){
		if (scoreV[i] < ver){
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
	else {
		//number
		min += 22;
	}
	return (min & 0xff);//chars[min];
}
