#pragma once
#include <string>
#include <vector>

#define WINDOWS
#ifdef WINDOWS
#include <stdio.h>
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

namespace Utility {
	//This returns wherever the code is that is executing, so werever the .exe is.
	extern std::string GetCurrentWorkingDir();

	//This returns getCurrentWorkingDir() with the last folder removed.  This is always the $(SolutionDir) when running in visual studio.
	extern std::string GetSolutionDir();

	/*
	*input - text: Text to be split along a delimiter.
	*		 delimiter: Optional delimiter to split about.
	*return - A vector whose elements are text inbetween the delimiters.
	*use - split("Hello World") = {"Hello", "World"}
	*/
	extern std::vector<std::string> Split(std::string text, std::string delimiter = " ");


	//Used to get random indexes from vectors
	extern int RandInt(int min, int max);

	//
	extern double RandDouble(double min, double max);
}

