#include "OCRPatternMatching.h"
#include "imageLib\ImageLoader.h"
#include <iostream>
#include <iomanip>

ImageGray OCRPatternMatching::Resample(ImageGray& input, int newWidth, int newHeight)
{
	//
	// Get a new buffer to interpolate into
	ImageGray newData = ImageGray(newWidth, newHeight);

	double scaleWidth = (double)newWidth / (double)input.width();
	double scaleHeight = (double)newHeight / (double)input.height();

	for (int cy = 0; cy < newHeight; cy++)
	{
		for (int cx = 0; cx < newWidth; cx++)
		{
			newData.at(cx, cy) = input.at((cx / scaleWidth), (cy / scaleHeight));
		}
	}
	return newData;
}


OCRPatternMatching::OCRPatternMatching()
{
	lastDetection = LAST_FOUND_STRIPE;
	referenceImages = std::vector<std::unique_ptr<ImageGray>>(NUMBER_OF_CHARACTERS);
	for (int i = 0; i < NUMBER_OF_CHARACTERS; i++) {
		referenceImages[i] = loadImg("C:\\Images\\font\\" + std::to_string(i) + ".png");
	}
}

void OCRPatternMatching::StartNewLicenseplate() {
	lastDetection = LAST_FOUND_STRIPE;
}

unsigned char OCRPatternMatching::Recognize(ImageGray& character) {
	float score[NUMBER_OF_CHARACTERS] = { };
	unsigned int index = 0;
	for (std::unique_ptr<ImageGray>& sample : referenceImages) {
		ImageGray resized = Resample(character, sample->width(), sample->height());

		/*/SAVE TEMP
		corona::Image* destination = corona::CreateImage(resized.width(), resized.height(), corona::PF_R8G8B8);
		unsigned char * pixels = (unsigned char*)destination->getPixels();
		//unsigned char * pixels = new unsigned char[character.width() * character.height() * 3];
		int count = 0;
		for (std::vector<unsigned char>::iterator it = resized.begin(); it != resized.end(); ++it) {
			pixels[count] = *it;
			pixels[count + 1] = *it;
			pixels[count + 2] = *it;
			count += 3;
		}
		std::string path = "C:\\Images\\RESIZE";
		path += std::to_string(index);
		path += ".png";
		corona::SaveImage(path.c_str(), corona::FF_PNG, destination);
		//DONE*/

		//resized input image has the same size as our sample from here
		for (unsigned int h = 0; h < sample->height(); h++) {
			for (unsigned int w = 0; w < sample->width(); w++) {
				if (sample->at(w, h) == resized.at(w, h)) {
					score[index] += 1;
				}
				/*else {
					score[index] -= 2;
				}*/
			}
		}
		score[index] = (float)score[index] / (resized.width() * resized.height()) * 100; //percentage
		if (score[index] > FIND_CHAR_PERCENTAGE)
			break;
		//score[index] = score[index] / (resized.width() * resized.height());
		++index;
	}
	int highestIndex = 0;
	float highestValue = 0;
	for (int i = 0; i < NUMBER_OF_CHARACTERS; i++) {
		if (score[i] > highestValue) {
			highestValue = score[i];
			highestIndex = i;
		}
	}

	int charIndex;
	if (highestIndex < CHAR_INDEX_SIZE) {
		//letter
		charIndex = highestIndex + ASCII_CONVERT_LETTER;
	}
	else if (highestIndex == CHAR_INDEX_SIZE) {
		charIndex = highestIndex + ASCII_CONVERT_STRIPE; //-
	}
	else {
		//number
		charIndex = highestIndex + ASCII_CONVERT_NUMBER;
	}
	char output = (charIndex & 0xff);
	if (output == '-')
		lastDetection = LAST_FOUND_STRIPE;
	else {
		if (highestIndex < CHAR_INDEX_SIZE && lastDetection == LAST_FOUND_NUMBER) {
			//found letter and our last detection was number
			//not possible
			if (output == 'O' || output == 'Q')
				output = '0';
		}
		else if (highestIndex > CHAR_INDEX_SIZE && lastDetection == LAST_FOUND_LETTER) {
			//found number and our last detection was letter
			//not possible
			if (output == '0') {
				if (score[O_INDEX] > score[Q_INDEX]) 
					output = 'O';
				else 
					output = 'Q';
			}
		}
		else {
			if (highestIndex < CHAR_INDEX_SIZE) {
				lastDetection = LAST_FOUND_LETTER; //set last found to letter
			}
			else {
				lastDetection = LAST_FOUND_NUMBER; //set last found to number
			}
		}
	}
	std::cout << std::setprecision(4) <<std::fixed << highestValue << "%\t";
	return output;//chars[min];
}
