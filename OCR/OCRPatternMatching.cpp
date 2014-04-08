#include "OCRPatternMatching.h"
#include "imageLib\ImageLoader.h"

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
	referenceImages = std::vector<std::unique_ptr<ImageGray>>(NUMBER_OF_CHARACTERS);
	for (int i = 0; i < NUMBER_OF_CHARACTERS; i++) {
		referenceImages[i] = loadImg("C:\\Images\\font\\" + std::to_string(i) + ".png");
	}
}

unsigned char OCRPatternMatching::Recognize(ImageGray& character) {
	signed int score[NUMBER_OF_CHARACTERS] = { };
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
		for (int h = 0; h < sample->height(); h++) {
			for (int w = 0; w < sample->width(); w++) {
				if (sample->at(w, h) == resized.at(w, h)) {
					score[index] += 1;
				}
				else {
					score[index] -= 2;
				}
			}
		}
		++index;
	}
	int highestIndex = 0;
	signed int highestValue = 0;
	for (int i = 0; i < NUMBER_OF_CHARACTERS; i++) {
		if (score[i] > highestValue) {
			highestValue = score[i];
			highestIndex = i;
		}
	}

	if (highestIndex < 26) {
		//letter
		highestIndex += 65;
	}
	else if (highestIndex == 26) {
		highestIndex += 19; //-
	}
	else {
		//number
		highestIndex += 21;
	}
	return (highestIndex & 0xff);//chars[min];
}
