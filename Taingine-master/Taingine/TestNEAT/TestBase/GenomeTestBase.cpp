#include "..\pch.h"
#include "GenomeTestBase.h"


std::filebuf* GenomeTestBase::fb;
std::istream* GenomeTestBase::stream;

std::istream* GenomeTestBase::SetUp(std::string path) {
	fb = new std::filebuf();
	if (!fb->open(path, std::ios::in)) {
		std::stringstream ss;
		ss << "Could not open file " << path << std::endl;
		throw std::exception(ss.str().c_str());
	}

	stream = new std::istream(fb);
	std::string header = FileUtility::readChar4(*stream);
	u8 version = FileUtility::readByte(*stream);
	u32 generation = FileUtility::readUnsignedInt(*stream);

	return stream;
}

void GenomeTestBase::TearDown() {
	fb->close();
	delete stream;
	delete fb;
}