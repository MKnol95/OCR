#include "splitLicensePlate.h"
#include <memory>

int main(int argc, char *argv[])
{
	//even testen
	Data::getInstance().initializeDefines(argv);
	splitLicensePlate* makeSplit = new splitLicensePlate();
	makeSplit->ProcessImage();
	makeSplit->WriteCSV();
	return 0;
}
