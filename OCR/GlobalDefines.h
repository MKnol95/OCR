#pragma once
#include <string>
typedef unsigned char byte;
class Data {
private:
	std::string baseFilePath;
	std::string baseFileName;
	std::string realFileName;
	Data() {}
	~Data() {}
	Data(const Data&) {}
	Data& operator = (const Data&);
public:
	std::string getPath() { return baseFilePath; }
	std::string getFile() { return baseFileName; }
	std::string getName() { return realFileName; }
	void initializeDefines(char *argv[]) {
		std::string tmpArgString = argv[1];
		baseFilePath = (tmpArgString.substr(0, tmpArgString.find_last_of('\\') + 1));
		baseFileName = (tmpArgString.substr(tmpArgString.find_last_of('\\') + 1, (tmpArgString.find_last_of('.') - tmpArgString.find_last_of('\\')) - 1));
		realFileName = (tmpArgString.substr(tmpArgString.find_last_of('\\') + 1, std::string::npos));
	}
	static Data & getInstance() {
		static Data instance;
		return instance;
	}
};

//filePath = (baseFileName.substr(0, baseFileName.find_last_of('/') + 1));
//originalFileName = (baseFileName.substr(baseFileName.find_last_of('/') + 1, std::string::npos));
