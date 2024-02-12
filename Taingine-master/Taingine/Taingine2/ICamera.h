#pragma once
#include <glm-0.9.8.5/glm/glm.hpp>

#include "Listener.h"

class ICamera {
public:
	virtual void move(float delta);
	virtual glm::vec3 getPosition();
	virtual glm::mat4 getViewMatrix();
	virtual glm::mat4 getProtectionMatrix();
	virtual glm::mat4 getProtectionViewMatrix();
	virtual void addMoveListener(Listener listener);
};


