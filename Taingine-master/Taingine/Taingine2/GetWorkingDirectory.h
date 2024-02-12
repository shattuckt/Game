#pragma once
#include <string>
#define WINDOWS
#ifdef WINDOWS
#include <stdio.h>
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

class GetWorkingDirectory{
	public:
		static std::string GetCurrentWorkingDir(void);
	};
