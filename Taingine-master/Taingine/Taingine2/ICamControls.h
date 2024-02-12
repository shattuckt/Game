#pragma once

class ICamControls {
public:
	virtual float getZoomImput();
	virtual float getPitchInput();
	virtual float getYawInput();
	virtual bool goRight();
	virtual bool goLeft();
	virtual bool goForwards();
	virtual bool goBackwards();
};
