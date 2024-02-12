#include "Maths.h"

Maths::Maths() {
}

//P1, P2, and P3 are the three points of the traingle while the pos is the 2D coordinate of the player
float Maths::barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y; //return the height of the player at the current position 
											  //NOTE: HEIGHTS[gridX][gridZ) are the top left of the tile (or top left triangle's right angle corner) - so it looks like (0, HEIGHTS[gridX][gridZ], 0)
											  //Therefore, the lower left corner (0,1) will be (0, heights[gridX][gridZ+1], 1)
											  //the top right corner (1,0) will be (1, heights[gridX+1][gridZ], 0)
											  //and finally, the bottom left, which is the bottom right triangle's right angle corner, will be (1, 1)
}

//2d textures (so the gui)...:
glm::mat4 Maths::createTransformationMatrix(glm::vec2 translation, glm::vec2 scale) {
	glm::mat4 matrix;
	matrix = glm::translate(matrix, glm::vec3(translation.x, translation.y, 0));
	matrix = glm::scale(matrix, glm::vec3(scale.x, scale.y, 1.0f));
	return matrix;
}

//This is called every frame
glm::mat4 Maths::createTransformationMatrix(glm::vec3 translation, float rx, float ry, float rz, float scale) {

	glm::mat4 matrix;
	matrix = glm::translate(matrix, translation);                      //translate on some vec3 array (means move)
	matrix = glm::rotate(matrix, glm::radians(rx), glm::vec3(1, 0, 0));  //rotate on the x axis
	matrix = glm::rotate(matrix, glm::radians(ry), glm::vec3(0, 1, 0));  //rotate on the y axis
	matrix = glm::rotate(matrix, glm::radians(rz), glm::vec3(0, 0, 1));  //rotate on the z axis
	matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));       //scale the matrix  
	return matrix; //return the matrix!

}




Maths::~Maths(void)
{}
