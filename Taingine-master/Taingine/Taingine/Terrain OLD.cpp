#include "Terrain.h"

const float TERRAINSIZE = 150;
const float MAX_HEIGHT = 40;
const float MAX_PIXEL_COLOUR = 256 * 256 * 256; 

Terrain::Terrain(int gridX, int gridZ, Loader loader, TerrainTexturePack texturePack, TerrainTexture blendMap, std::string heightMap) {
	texturePacks = texturePack;
	blendMaps = blendMap;
	x = gridX * TERRAINSIZE;
	z = gridZ * TERRAINSIZE;
	models = generateTerrain(loader, heightMap);
	terrainSize = TERRAINSIZE;
}

RawModel Terrain::generateTerrain(Loader loader, std::string heightMap) {

	int width, height, nrChannels;
	//stbi_set_flip_vertically_on_load(true); //This flips the image. might be needed sometimes
	getPaths getPath; //lets get the path of the texture. right now this assumes it is in the 'res' folder. 
	std::string filePath = getPath.GetCurrentWorkingDir() + "\\res\\" + heightMap + ".png";
	//std::cout << "Filename inside of loadTexture is " << filePath << std::endl;
	unsigned char *heightmapImage = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 4); //This loads the texture from said location

	GLenum format; //This makes it where if a file does not have a alpha values, those values will not be loaded. 
	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3) {
		std::cout << "There are NO slpha values inside of " << heightMap << "!" << std::endl;
		format = GL_RGB;
	}
	else if (nrChannels == 4) {
		std::cout << "There are slpha values inside of " << heightMap << "!" << std::endl;
		format = GL_RGBA;
	}
	int channelNum = nrChannels; //Since stbi will load a null alpha field for PNG files without alpha values, we must find out if a file has alpha values
	heightmapImage = stbi_load(filePath.c_str(), &width, &height, &nrChannels, channelNum); //reload the image with the correct number of channels... 

																							//std::cout << "*********************Height of heightmap is " << height << std::endl;
	int VERTEX_COUNT = height; //each pixel represents the height of a certain pixel.. 
	heights.resize(VERTEX_COUNT, std::vector<float>(VERTEX_COUNT, 0)); //Resize the vector to vertex count x vertex count
	int count = VERTEX_COUNT * VERTEX_COUNT;
	std::vector<float> vertices(count * 3);
	std::vector<float> normals(count * 3);
	std::vector<float> textureCoords(count * 2);
	std::vector<unsigned int> indices(6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1));
	int vertexPointer = 0;
	for (int i = 0; i<VERTEX_COUNT; i++) {
		for (int j = 0; j<VERTEX_COUNT; j++) {
			vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * TERRAINSIZE;
			float thisheight = getHeight(j, i, heightmapImage, width, height, channelNum);
			heights[j][i] = thisheight;
			vertices[vertexPointer * 3 + 1] = thisheight; //this depicts the height so we will put the height function here... 
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * TERRAINSIZE;
			glm::vec3 normal = calculateNormal(j, i, heightmapImage, width, height, channelNum);
			//normals[vertexPointer * 3] = 0;
			//normals[vertexPointer * 3 + 1] = 1;
			//normals[vertexPointer * 3 + 2] = 0;
			normals[vertexPointer * 3] = normal.x;
			normals[vertexPointer * 3 + 1] = normal.y;
			normals[vertexPointer * 3 + 2] = normal.z;
			textureCoords[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
			textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
			vertexPointer++;
		}
	}
	int pointer = 0;
	for (int gz = 0; gz<VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx<VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}

	float* verticesArray = &vertices[0];
	float* texturedArray = &textureCoords[0];
	float* normalArray = &normals[0];
	unsigned int* indicesArray = &indices[0];

	stbi_image_free(heightmapImage); //free up the picture

	return loader.loadToVAO(vertices, textureCoords, normals, indices);

}

//By default, all normals on the texture point straight up. which would make everything be one color
glm::vec3 Terrain::calculateNormal(int x, int z, unsigned char* image, int width, int height, int nrChannels) {
	//The point of this function is to use surrounding points to find the corresponding vector for each pixel

	unsigned int bytePerPixel = nrChannels;
	//std::cout << "The top left RGB of the image is R: " << (int)image[0] << " G: " << (int)image[1] << " B: " << (int)image[2] << std::endl;
	//std::cout << "The bottom left RGB of the image is R: " << (int)image[765] << " G: " << (int)image[766] << " B: " << (int)image[767] << std::endl;

	//print each coord in heightmap..
	//std::cout << "X is " << x << " and Z is " << z << std::endl;
	//the last pixel color - this is for a 256x256 image... 
	//std::cout << "Final color is R:" << (int)image[262140] << " G: " << (int)image[262141] << " B: " << (int)image[262142] << " A: " << (int)image[262143] << std::endl;

	//In order to access a pixel of any shape image. Remember that X is what gets incremented for each pixel while Z gets incremented for each row. 
	//In other words, the top left pixel would be image[0-3] but the next column over would be image[1024-1027]
	//This means for any x,z coord on a texture, its RGBA starting location will be image[(z * width * 4) + (x * 4) + 0]
	//unsigned char* heightL = image + (z * width * 4) + ((x - 1) * 4) * bytePerPixel;
	//std::cout << "left is R: " << (int)RgbSet1[0] << " G: " << (int)RgbSet1[1] << " B: " << (int)RgbSet1[2] << " A: " << (int)RgbSet1[3] << std::endl;
	//unsigned char* heightR = image + (z * width * 4) + ((x + 1) * 4) * bytePerPixel;
	//unsigned char* heightD = image + ((z - 1) * width * 4) + (x * 4) * bytePerPixel;
	//unsigned char* heightU = image + ((z + 1) * width * 4) + (x * 4) * bytePerPixel;

	//idk why im such an idiot. you just need the x and z coordinate and then find the height of that spot ... 
	float heightL = getHeight(x - 1, z, image, width, height, nrChannels);
	float heightR = getHeight(x + 1, z, image, width, height, nrChannels);
	float heightD = getHeight(x, z - 1, image, width, height, nrChannels);
	float heightU = getHeight(x, z + 1, image, width, height, nrChannels);

	glm::vec3 normal = glm::vec3(heightL - heightR, 2.0f, heightD - heightU);

	glm::normalize(normal); //ensure the vector is less than 1... 
							//std::cout << "the normal calculation is: R: " << normal.x << " G: " << normal.y << " B: " << normal.z << std::endl;
	return normal;
}
float Terrain::getHeight(int x, int z, unsigned char* image, int width, int height, int nrChannels) {
	if (x < 0 || x >= width || z < 0 || z >= height) {
		return 0;
	}
	unsigned bytePerPixel = nrChannels;
	unsigned char* RgbSet = image + (x + width * z) * bytePerPixel;
	int r = (int)RgbSet[0];
	int g = (int)RgbSet[1];
	int b = (int)RgbSet[2];
	float totalHeight = r + g + b; //Note: in order to get at Y = 0, you would need about R: 201 G: 201 B: 201.
								   //float totalHeight = r * g * b;
								   //std::cout << "r: " << r << " g: " << g << " b: " << b << std::endl;

	totalHeight -= MAX_PIXEL_COLOUR / 2.0f; //This is supposed to return a value between MAXPIXEL/2 and -MAXPIXEL/2 
											//note: for some reason java returns a negative number for the int value, so we subtract since we will always get a positive number. 
	totalHeight /= MAX_PIXEL_COLOUR / 2.0f; //This will give us a value between -1 and 1 which we can then use to scale the terrain.. 
	totalHeight *= MAX_HEIGHT; //now use our number between -1 and 1 to give us a final height... 
							   //std::cout << "totalHeight = " << totalHeight << std::endl;

	return totalHeight;

}

float Terrain::getX() {
	return x;
}
float Terrain::getZ() {
	return z;
}
float Terrain::getTerrainSize() {
	return terrainSize;
}
RawModel Terrain::getModel() {
	return models;
}
TerrainTexturePack Terrain::getTexturePacks() {
	return texturePacks;
}
TerrainTexture Terrain::getBlendMap() {
	return blendMaps;
}

float Terrain::getHeightOfTerrain(float worldX, float worldZ) {
	float terrainX = worldX - x;
	float terrainZ = worldZ - z;
	float gridSquareSize = TERRAINSIZE / (heights.size() - 1); //if there are 4 vertices (4 points), there would only be 3 texture tiles
	if (gridSquareSize < 1) { //This is meant to be a checker if the terrain simply isn't there 
		//std::cout << "NO TERRAIN HAS BEEN GENERATED..." << std::endl;
		return 0;
	}
	unsigned int gridX = (int)floor(terrainX / gridSquareSize); //The ground is a 2D matrix - as long as you have the correct position in the 
	unsigned int gridZ = (int)floor(terrainZ / gridSquareSize); //grid that is all you need to access the correct value for the height
	if (gridX >= heights.size() - 1 || gridZ >= heights.size() - 1 || gridX < 0 || gridZ < 0) { //THIS MIGHT CAUSE A CRASH ONCE YOU REACH THE EDGE OF THE TERRAIN
		return 0;
	}
	float xCoord = ((int)terrainX % (int)gridSquareSize) / gridSquareSize; //not sure if converting float to int will result in loss in data
	float zCoord = ((int)terrainZ % (int)gridSquareSize) / gridSquareSize; //both this line and the previous will return Y and Z coordinates between zero and one.
																		   //Note: the top left of a grid is (0,0) and the bottom right is (1,1)

																		   //The hypotenuse of the two triangles creating the square has the coordinates of 1 = x + y where x and y are between one and zero
																		   //If the X coordinate is greater than 1 - Z, then it is in the bottom right triangle (the one with (1,1) as its right angle corner
																		   //If the X coordinate is less than 1 - Z, then it is in the top left triangle (the one with (0,0) as its right angle corner
	float answer;
	Maths maths;
	//So now we will use the Barrycentric function to find the height of the player at coordinate X, Z
	if (xCoord <= (1 - zCoord)) { //so if the coordinate is in the top left triangle
		answer = maths.barryCentric(glm::vec3(0, heights[gridX][gridZ], 0),
			glm::vec3(1, heights[gridX + 1][gridZ], 0), glm::vec3(0, heights[gridX][gridZ + 1], 1),
			glm::vec2(xCoord, zCoord));
	}
	else { //else.. the coordinate is in the bottom right triangle
		answer = maths.barryCentric(glm::vec3(1, heights[gridX + 1][gridZ], 0),
			glm::vec3(1, heights[gridX + 1][gridZ + 1], 1), glm::vec3(0, heights[gridX][gridZ + 1], 1),
			glm::vec2(xCoord, zCoord));
	}
	return answer;
}
Terrain::~Terrain(void)
{
}
