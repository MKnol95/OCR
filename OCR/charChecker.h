#pragma once
#include <corona.h>
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include "imageLib\ImageGray.h"
#define NUMBER_OF_CHARACTERS 37
#define HORIZONTAL_HISTOGRAM_SIZE 30 //15
#define VERTICAL_HISTOGRAM_SIZE 36 //18

using namespace ImageLib;

//! class CharChecker
//
//! @authors Rick van der Paauw, Marco Knol, Melvin van den Berg and Michael Pieneman
//! This class uses histograms to recognize chars. In the header are the sample histograms (horizontal and vertical) for each character, the stripe and the numbers 0 to 9.
//! From each input character a histogram is created, which will be compared with the sample histograms. 
//! The histogram contains the number of black pixels on the row (vertical) or column (horizontal).
//! Every number of black pixels that differs from the sample number of black pixels will get the score of the difference of the number of black pixels in the input and the number of black pixels in the sample. 
//! The character with the lowest score (= the slightest difference between the sample and input) is presumably the character. 
class CharChecker
{
private:
	//! @var Char is used to store the character that got the lowest score. 
	char Char;
	//! @var horizontal is used to determine which histogram (horizontal or vertical) is needed.
	bool horizontal;
	//! @var scoreH stores the score for the horizontal histograms per character/number/stripe.
	int scoreH[NUMBER_OF_CHARACTERS];
	//! @var scoreV stores the score for the vertical histograms per character/number/stripe.
	int scoreV[NUMBER_OF_CHARACTERS];
	//! @var csvDataH stores the number of black pixels per column of the input picture.
	unsigned short csvDataH[HORIZONTAL_HISTOGRAM_SIZE];
	//! @var csvDataV stores the number of black pixels per row of the input picture.
	unsigned short csvDataV[VERTICAL_HISTOGRAM_SIZE];
	//! Inter1parray
	//
	//! @param a is the input vector that needs interpolation and stretching.
	//! @param horizontal knows if the vector needs to be scaled to the horizontal or vertical histogram size. 
	//! Scales the number of black pixels on the horizontal and vertical histogram over the length of the sample histogram.
	//! This is done by interpolation, to avoid faulty results of the scaling. 
	void inter1parray(std::vector<int> a, bool horizontal);
public:
	//! CharChecker constructor
	//
	//! @param csvDataInputH is the data of the input horizontal histogram. 
	//! @param csvDataInputV is the data of the input vertical histogram. 
	//! @param hor knows if the horizontal or vertical histogram samples are used. 
	//! The constructor sets the horizontal variable on true or false and clears the scores. 
	//! Also the input histograms are scaled and interpolated.
	CharChecker(std::vector<int>& csvDataInputH, int height, std::vector<int>& csvDataInputV, bool hor);
	//! GetChar
	//
	//! Returns (if the process() has runned) the character with the lowest score. 
	char& getChar();
	//! Execute the char checking process.
	//
	//! Perform the needed actions to find the best matching histogram and determine the character.
	char process();
};

