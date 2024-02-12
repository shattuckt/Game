#pragma once
#include <istream>
#include <ostream>

typedef unsigned __int8 u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

namespace FileUtility {
	extern u8 readByte(std::istream& file);
	extern void writeByte(std::ostream& file, u8 value);
	extern u16 readUnsignedShort(std::istream& file);
	extern void writeUnsignedShort(std::ostream& file, u16 value);
	extern u32 readUnsignedInt(std::istream& file);
	extern void writeUnsignedInt(std::ostream& file, u32 value);
	extern float readFloat(std::istream& file);
	extern void writeFloat(std::ostream& file, float value);
	extern u64 readUnsingedLongLong(std::istream& file);
	extern void writeUnsignedLongLong(std::ostream& file, u64 value);
	extern double readDouble(std::istream& file);
	extern void writeDouble(std::ostream& file, double value);
	extern int readInt(std::istream& file);
	extern void writeInt(std::ostream& file, int value);
	extern std::string readString(std::istream& file);
	extern std::string readString(std::istream& file, int length);
	extern void writeString(std::ostream& file, std::string value);
	extern std::string readChar4(std::istream& file);
	extern void writeChar4(std::ostream& file, std::string header);
}
