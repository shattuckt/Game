#include "pch.h"
#include "Utility.h"

//TEST(UtilityTest, GetWorkingDirTest) {
//	std::string expected = "C:\\SBTS\\Taingine\\Taingine\\Taingine\\x64\\Debug";
//	std::string actual = Utility::getCurrentWorkingDir();
//
//	EXPECT_EQ(expected, actual);
//}
//
//TEST(UtilityTest, GetSolutionDirTest) {
//	std::string expected = "C:\\SBTS\\Taingine\\Taingine\\Taingine\\";
//	std::string actual = Utility::getSolutionDir();
//
//	EXPECT_EQ(expected, actual);
//}

TEST(UtilityTest, SplitDefaultTest) {
	std::vector<std::string> expected{ "Word1", "Word2", "Word3", "Word4" };
	std::string input = "Word1 Word2 Word3 Word4";
	std::vector<std::string> actual = Utility::Split(input);

	EXPECT_EQ(expected, actual);
}

TEST(UtilityTest, SplitPassedDelimiterTest) {
	std::vector<std::string> expected{ "Word1", "Word2", "Word3" };
	std::string input = "Word1,Word2,Word3";
	std::vector<std::string> actual = Utility::Split(input, ",");

	EXPECT_EQ(expected, actual);
}

TEST(UtilityTest, SplitMultiCharDelimiterTest) {
	std::vector<std::string> expected{ "Word1", "Word2", "Word3" };
	std::string input = "Word1,|Word2,|Word3";
	std::vector<std::string> actual = Utility::Split(input, ",|");

	EXPECT_EQ(expected, actual);
}
