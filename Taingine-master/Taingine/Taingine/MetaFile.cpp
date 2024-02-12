#include "MetaFile.h"

const int HEIGHT = 180; //180   720;
const int PAD_TOP = 0;
const int PAD_LEFT = 1;
const int PAD_BOTTOM = 2;
const int PAD_RIGHT = 3;

const int DESIRED_PADDING = 8; //amount of empty space around text characters when rendered

const char SPLITTER = ' ';
const std::string NUMBER_SEPARATOR = ",";

const double LINE_HEIGHT = 0.03f;
const int SPACE_ASCII = 32;

MetaFile::MetaFile(std::string file, DisplayManager* display) {
	this->aspectRatio = display->getAspectRatio();
	fileReader = new std::filebuf(); 
	getPaths getPath;
	std::string filePath;
	filePath = getPath.GetCurrentWorkingDir() + "\\res\\" + file;

	if (!fileReader->open(filePath, std::ios::in)) {
		std::stringstream ss;
		ss << "Could not open file " << filePath << std::endl;
		throw std::exception(ss.str().c_str());
	} 

	this->stream = new std::ifstream(filePath);
	
	loadPaddingData();
	loadLineSizes();
	int imageWidth = getValueOfVariable("scaleW");
	loadCharacterData(imageWidth);
	close();
}
MetaFile::MetaFile() { //default constructor
	this->aspectRatio = -1;
}

void MetaFile::close() {
	fileReader->close();
	delete stream;
	delete fileReader;
}

double MetaFile::getSpaceWidth() {
	return this->spaceWidth;
}
Character* MetaFile::getCharacter(int ascii) {
	return metaData[ascii];
}
bool MetaFile::processNextLine() {
	values.clear();
	std::string line; //stream = new std::istream(fb);
	std::cout << "About to process line" << std::endl;
	try {
		if (std::getline(*stream, line)) {
			std::cout << "Line : " << line << std::endl;
			stringstream lineToIterateThrough(line);
			while (std::getline(lineToIterateThrough, line, SPLITTER)) {
				std::cout << "MetaFile line 57 line: " << line << std::endl;
				stringstream keyValuePair(line);
				std::vector<std::string> keyValuePlaceholder;
				std::string holder;
				while (std::getline(keyValuePair, holder, '=')) {
					keyValuePlaceholder.push_back(holder);
				}
				if (keyValuePlaceholder.size() == 2) {
					values.insert({ keyValuePlaceholder[0],keyValuePlaceholder[1] });
				}
				keyValuePlaceholder.clear();

			}
			std::cout << "KEY\tELEMENT\n";
			for (auto itr = values.begin(); itr != values.end(); itr++) {
				cout << itr->first
					<< '\t' << itr->second << '\n';
			}
		}
		else
			return false;
	}
	catch (const std::overflow_error & e) {
		std::cout << "Error reading line: " << e.what() << std::endl;
	}
	return true;
}

int MetaFile::getValueOfVariable(std::string variable) {
	return std::stoi(values[variable]);
}

std::vector<int> MetaFile::getValuesOfVariable(std::string variable) {
	stringstream fieldValueStream(values[variable]);
	std::vector<int> multiValueHolder;
	std::string holder;
	std::cout << "Attempting to getValueofVariable: " << variable << std::endl;
	while (std::getline(fieldValueStream, holder, ',')) {
		multiValueHolder.push_back(std::stoi(holder));
		std::cout << "Pushed back value " << std::stoi(holder) << std::endl;
	}
	return multiValueHolder;
}


void MetaFile::loadPaddingData() {
	processNextLine();
	this->padding = getValuesOfVariable("padding");
	this->paddingWidth = padding[PAD_LEFT] + padding[PAD_RIGHT];
	this->paddingHeight = padding[PAD_TOP] + padding[PAD_BOTTOM];
}

void MetaFile::loadLineSizes() {
	processNextLine();
	int lineHeightPixels = getValueOfVariable("lineHeight") - paddingHeight;
	this->verticalPerPixelSize = LINE_HEIGHT / (double)lineHeightPixels;
	this->horizontalPerPixelSize = this->verticalPerPixelSize / aspectRatio;
}

void MetaFile::loadCharacterData(int imageWidth) {
	processNextLine();
	processNextLine();
	while (processNextLine()) {
		Character* c = loadCharacter(imageWidth);
		if (c != NULL) {
			int test = c->getID();
			metaData.insert({ test,c });
		}
	}
}

Character* MetaFile::loadCharacter(int imageSize) {
	int id = getValueOfVariable("id");
	if (id == 32) { //TextMeshCreator.SPACE_ASCII
		this->spaceWidth = (getValueOfVariable("xadvance") - paddingWidth) * horizontalPerPixelSize;
		return NULL;
	}
	double xTex = ((double)getValueOfVariable("x") + (padding[PAD_LEFT] - DESIRED_PADDING)) / imageSize;
	double yTex = ((double)getValueOfVariable("y") + (padding[PAD_TOP] - DESIRED_PADDING)) / imageSize;
	int width = getValueOfVariable("width") - (paddingWidth - (2 * DESIRED_PADDING));
	int height = getValueOfVariable("height") - ((paddingHeight)-(2 * DESIRED_PADDING));
	double quadWidth = width * horizontalPerPixelSize;
	double quadHeight = height * verticalPerPixelSize;
	double xTexSize = (double)width / imageSize;
	double yTexSize = (double)height / imageSize;
	double xOff = (getValueOfVariable("xoffset") + padding[PAD_LEFT] - DESIRED_PADDING) * horizontalPerPixelSize;
	double yOff = (getValueOfVariable("yoffset") + (padding[PAD_TOP] - DESIRED_PADDING)) * verticalPerPixelSize;
	double xAdvance = (getValueOfVariable("xadvance") - paddingWidth) * horizontalPerPixelSize;
	return new Character(id, xTex, yTex, xTexSize, yTexSize, xOff, yOff, quadWidth, quadHeight, xAdvance);
}

