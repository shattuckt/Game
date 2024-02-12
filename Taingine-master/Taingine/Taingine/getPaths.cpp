#include "getPaths.h"


getPaths::getPaths(void)
{
}

std::string getPaths::GetCurrentWorkingDir(void) {

	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;

}

getPaths::~getPaths(void)
{
}
