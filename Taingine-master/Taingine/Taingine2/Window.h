#pragma once
#include <vector>

#include "WindowSizeListener.h"
#include "Sync.h"
#include "WindowBuilder.h"

//The interaction between this class and WindowBuilder isn't ideal. WIth the circle dependency created here, it is 
	// likely better to just use one class. Maybe bring this back up with Taylor once the rest of the game is setup.
class WindowBuilder;  //try taking this out later. see if friend delcaration is good enough.

class Window{
	friend class WindowBuilder;
private:
	GLFWwindow* id;
	Sync* frameSync;

	int pixelWidth, pixelHeight;
	int desiredWidth, desiredHeight;
	int widthScreenCoords, heightScreenCoords;

	bool fullscreen;
	bool vsync;
	int fps;

	std::vector<WindowSizeListener*> listeners;

	void switchToFullScreen(GLFWmonitor* monitor, const GLFWvidmode* vidMode);
	void switchToWindowed(const GLFWvidmode* vidMode);
	void addScreenSizeListener();
	void addPixelSizeListener();
	void getInitialWindowSizes();
	void getInitialScreenSize();
	void getInitialPixelSize();
	bool validSizeChange(int newWidth, int newHeight, int oldWidth, int oldHeight);
	void notifyListeners();  


protected:
	Window(GLFWwindow* id, int desiredWidth, int desiredHeight, int fps, bool fullscreen, bool vsync);

public:
	static WindowBuilder* newWindow(int width, int height, std::string title);
	GLFWwindow* getId();
	int getScreenCoordWidth();
	int getScreenCoordHeight();
	int getFps();
	float getAspectRatio();
	int getPixelHeight();
	int getPixelWidth();
	bool isFullScreen();
	bool isVsync();
	void setFps(int fps);
	void addSizeChangeListener(WindowSizeListener* listener); //why not just use the callback for this?
	void update();
	bool closeButtonPressed();
	void destroy();
	void setVsync(bool vsync);
	void goFullScreen(bool fullscreen);



};

