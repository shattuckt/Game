#include "GetWorkingDirectory.h"
std::string GetWorkingDirectory::GetCurrentWorkingDir(void) {

	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;

}
