#include "FileUtility.h"


u8 FileUtility::readByte(std::istream& file) {
	u8 bytes[1];

	file.read((char*)bytes, 1);

	return bytes[0];
}


void FileUtility::writeByte(std::ostream& file, u8 value) {
	u8 bytes[1];

	// extract the individual bytes from our value
	bytes[0] = (value) & 0xFF;

	// write those bytes to the file
	file.write((char*)bytes, 1);
}


u16 FileUtility::readUnsignedShort(std::istream& file) {

	u16 value;
	u8 bytes[2];

	file.read((char*)bytes, 2);
	value = bytes[0] | (bytes[1] << 8);

	return value;
}


void FileUtility::writeUnsignedShort(std::ostream & file, u16 value) {
	u8 bytes[2];

	// extract the individual bytes from our value
	bytes[0] = (value) & 0xFF;  // low byte
	bytes[1] = (value >> 8) & 0xFF;  // high byte

	// write those bytes to the file
	file.write((char*)bytes, 2);
}


u32 FileUtility::readUnsignedInt(std::istream & file) {
	u32 value;
	u8 bytes[4];

	file.read((char*)bytes, 4);
	value = bytes[3];
	for (int ie = 3; ie >= 0; ie--) {
		value = (value << 8) | bytes[ie];
	}

	return value;
}


void FileUtility::writeUnsignedInt(std::ostream & file, u32 value) {
	u8 bytes[4];
	// extract the individual bytes from our value
	bytes[0] = (value) & 0xFF;
	bytes[1] = (value >> 8) & 0xFF;
	bytes[2] = (value >> 16) & 0xFF;
	bytes[3] = (value >> 24) & 0xFF;


	// write those bytes to the file
	file.write((char*)bytes, 8);
}


void FileUtility::writeFloat(std::ostream& file, float value) {
	u32 unsignedValue;
	memcpy(&unsignedValue, &value, sizeof(unsignedValue));
	FileUtility::writeUnsignedInt(file, unsignedValue);
}


float FileUtility::readFloat(std::istream& file) {
	u32 unsignedValue = FileUtility::readUnsignedInt(file);
	float doubleValue;
	memcpy(&doubleValue, &unsignedValue, sizeof(doubleValue));

	return doubleValue;
}


u64 FileUtility::readUnsingedLongLong(std::istream & file) {
	u64 value;
	u8 bytes[8];

	file.read((char*)bytes, 8);
	value = bytes[7];
	for (int ie = 6; ie >= 0; ie--) {
		value = (value << 8) | bytes[ie];
	}

	return value;
}


void FileUtility::writeUnsignedLongLong(std::ostream & file, u64 value) {
	u8 bytes[8];
	u64 i;

	// extract the individual bytes from our value
	bytes[0] = (value) & 0xFF;
	bytes[1] = (value >> 8) & 0xFF;
	bytes[2] = (value >> 16) & 0xFF;
	bytes[3] = (value >> 24) & 0xFF;
	bytes[4] = (value >> 32) & 0xFF;
	bytes[5] = (value >> 40) & 0xFF;
	bytes[6] = (value >> 48) & 0xFF;
	bytes[7] = (value >> 56) & 0xFF;


	// write those bytes to the file
	file.write((char*)bytes, 8);
}


double FileUtility::readDouble(std::istream & file) {
	u64 unsignedValue = FileUtility::readUnsingedLongLong(file);
	double doubleValue;
	memcpy(&doubleValue, &unsignedValue, sizeof(doubleValue));

	return doubleValue;
}


void FileUtility::writeDouble(std::ostream & file, double value) {
	u64 unsignedValue;
	memcpy(&unsignedValue, &value, sizeof(unsignedValue));
	FileUtility::writeUnsignedLongLong(file, unsignedValue);
}


int FileUtility::readInt(std::istream & file) {
	u32 value = FileUtility::readUnsignedInt(file);
	return static_cast<int>(value);
}


void FileUtility::writeInt(std::ostream & file, int value) {
	u32 uint = static_cast<u32>(value);
	FileUtility::writeUnsignedInt(file, uint);
}


std::string FileUtility::readString(std::istream & file) {
	u32 length = FileUtility::readUnsignedInt(file);

	return readString(file, length);
}


std::string FileUtility::readString(std::istream & file, int length) {
	char* buffer = new char[length];
	file.read(buffer, length);

	std::string value(buffer, length);
	delete[] buffer;

	return value;
}


void FileUtility::writeString(std::ostream & file, std::string value) {
	u32 length = value.length();

	FileUtility::writeUnsignedInt(file, length);
	file.write(value.c_str(), length);
}


std::string FileUtility::readChar4(std::istream & file) {
	return readString(file, 4);
}


void FileUtility::writeChar4(std::ostream & file, std::string header) {
	file.write(header.c_str(), 4);
}