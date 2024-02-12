#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct DisplaySizes {
	struct DisplaySize {
		std::string name;
		int width;
		int height;
		int indice;

		DisplaySize(std::string name, int width, int height, int indice);
		int getWidth();
		int getHeight();
		int getIndice();
		std::string getName();
	};
	static const std::vector<DisplaySizes::DisplaySize> getSizes();
};

