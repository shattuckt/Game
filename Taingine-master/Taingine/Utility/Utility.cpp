#include "Utility.h"


std::string Utility::GetCurrentWorkingDir() {
	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
}

std::string Utility::GetSolutionDir() {
	std::string workingDir = GetCurrentWorkingDir();
	size_t lastSlash = workingDir.find_last_of("\\"); //At least in development this will get the solution directory by removing the "Debug/" portion of the file path.
	std::string result = workingDir.substr(0, lastSlash); //Remove the "Debug/" in the path.
	lastSlash = result.find_last_of("\\");
	return result.substr(0, lastSlash + 1);
}


std::vector<std::string> Utility::Split(std::string text, std::string delimiter) {
	std::vector<std::string> result;
	std::string subString;
	size_t position = 0; //Starting position of the substring.
	size_t secondPos = text.find(delimiter); //Where the first delimiter is found, ie the end of the substring.

	while (secondPos != std::string::npos) {//We do this so that we dont have to manipulate the string directly, making it more efficent
		subString = text.substr(position, secondPos - position);
		result.push_back(subString);
		position = secondPos + delimiter.length(); //This makes sure we skip the delimiter in the next cycle so that we dont ever obtain it in the result.
		secondPos = text.find(delimiter, position);
	}
	result.push_back(text.substr(position, secondPos));//Since we were at the end we need to get the last string that didnt have a delimiter behind it.

	return result;
}


int Utility::RandInt(int min, int max) {
	return min + (rand() % static_cast<int>(max - min + 1));
}


double Utility::RandDouble(double min, double max) {
	double start = (double)rand() / RAND_MAX;
	return min + start * (max - min);
}