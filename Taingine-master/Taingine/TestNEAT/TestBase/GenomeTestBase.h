#pragma once
#include "FileUtility.h"
#include <fstream>
#include <string>


namespace GenomeTestBase {
	extern std::filebuf* fb;
	extern std::istream* stream;
	extern std::istream* SetUp(std::string path);
	extern void TearDown();
}

