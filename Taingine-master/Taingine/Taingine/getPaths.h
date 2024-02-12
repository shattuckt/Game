#pragma once
#include <string>
//The following is for the GetCurrentWorkingDir function
#define WINDOWS
#ifdef WINDOWS
#include <stdio.h>
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

class getPaths
{
public:
	getPaths(void);

	std::string GetCurrentWorkingDir(void);

	~getPaths(void);
};

