#pragma once

class WindowSizeListener {
public:
	//void sizeChanged(int width, int height);
	virtual void sizeChanged(int width, int height) = 0;
};
