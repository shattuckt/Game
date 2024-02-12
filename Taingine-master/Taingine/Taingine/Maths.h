#pragma once
#include <glm-0.9.8.5\glm\glm.hpp>
#include <glm-0.9.8.5\glm\gtc\matrix_transform.hpp>
#include <glm-0.9.8.5\glm\gtx\string_cast.hpp>

class Maths
{
private:
	//Camera* camera;
	//glm::mat4 projectionMatrix;


public:
	Maths();

	float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);

	glm::mat4 createTransformationMatrix(glm::vec2 translation, glm::vec2 scale);
	glm::mat4 createTransformationMatrix(glm::vec3 translation, float rx, float ry, float rz, float scale);


	~Maths(void);
};

