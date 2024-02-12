#include "Loader.h"



//Just as review, VAO's are the container for datasets of VBOs. Think of a VAO as a table with an ID and content (column 1 and 2) and VBOs being
//just an array of content...

Loader::Loader() {}

//Create the VAO
int Loader::createVAO() {

	unsigned int vaoID;
	glGenVertexArrays(1, &vaoID);

	//Add the ID of the new VAO into our vector list
	vaos.push_back(vaoID);

	glBindVertexArray(vaoID);
	return vaoID;

}

//Creates a VAO and stores the position data of the vertices into attribute 0 of the VAO. The indices are stored in an index buffer and bound ot the VAO. 
//It appears in order to consistently receive the correct array size, it has to be passed from the function in which the array was created i.e. sizeof(positions) in this function will always be 1
//even though it is actually 4*(the amount of vertices).. 
RawModel Loader::loadToVAO(std::vector<float> positions, std::vector<float> textureCoords, std::vector<float> normals, std::vector<unsigned int> indices) {
	int vaoID = createVAO();
	bindIndicesBuffer(indices); //bind Indices works for integers - hence why there are two functions
	storeDataInAttributeList(0, 3, positions); //All positions are placed in VAO #1 - aka the first VBO. Second element is how large each section of the dataset is... 
	storeDataInAttributeList(1, 2, textureCoords); //All texture coords are placed in VBO #2. Since they are simple 2D coordinates they have a section size of 2...
	storeDataInAttributeList(2, 3, normals); //All normal vectors are laoded into VAO #3
	unbindVAO(); //Unbind the VAO once you are done using it
	return RawModel(vaoID, indices.size()); //So how many indices total, divide by 4 since it is a float value. 

}

RawModel Loader::loadToVAO(std::vector<float> positions, std::vector<float> textureCoords, std::vector<float> normals, std::vector<float> tangents, std::vector<unsigned int> indices) {
	int vaoID = createVAO();
	bindIndicesBuffer(indices); //bind Indices works for integers - hence why there are two functions
	storeDataInAttributeList(0, 3, positions); //All positions are placed in VAO #1 - aka the first VBO. Second element is how large each section of the dataset is... 
	storeDataInAttributeList(1, 2, textureCoords); //All texture coords are placed in VBO #2. Since they are simple 2D coordinates they have a section size of 2...
	storeDataInAttributeList(2, 3, normals); //All normal vectors are laoded into VAO #3
	storeDataInAttributeList(3, 3, tangents);
	unbindVAO(); //Unbind the VAO once you are done using it
	return RawModel(vaoID, indices.size()); //So how many indices total, divide by 4 since it is a float value. 

}

int Loader::loadToVAO(std::vector<float> positions, std::vector<float> textureCoords) {
	int vaoID = createVAO();
	storeDataInAttributeList(0, 2, positions); //All positions are placed in VAO #1 - aka the first VBO. Second element is how large each section of the dataset is... 
	storeDataInAttributeList(1, 2, textureCoords); //All texture coords are placed in VBO #2. Since they are simple 2D coordinates they have a section size of 2...
	unbindVAO(); //Unbind the VAO once you are done using it
	return vaoID;

}


RawModel Loader::loadToVAO(std::vector<float> positions, int dimensions) {
	int vaoID = createVAO();
	storeDataInAttributeList(0, dimensions, positions);
	unbindVAO();
	return RawModel(vaoID, positions.size() / dimensions); //each position is an x,y coordinate... 
}

int Loader::createEmptyVbo(int floatCount) {
	unsigned int vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, floatCount * 4, NULL, GL_STREAM_DRAW); 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return vboID;
}

void Loader::addInstancedAttribute(int vaoID, int vboID, int attribute, int dataSize, int instancedDataLength, int offset) {
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBindVertexArray(vaoID);
	glVertexAttribPointer(attribute, dataSize, GL_FLOAT, GL_FALSE, instancedDataLength * 4, (void*)(offset * 4));
	glVertexAttribDivisor(attribute, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Loader::updateVbo(int vboID, std::vector<float> data) {
	if (data.size() > 0) {
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, data.size() * 4, NULL, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * 4, &data[0]);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

TextureData Loader::processTexture(std::string fileName) {

	int width, height, nrChannels;
	getPaths getPath; //lets get the path of the texture. right now this assumes it is in the 'res' folder. 
	std::string filePath = getPath.GetCurrentWorkingDir() + "\\res\\" + fileName;
	unsigned char *texture = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0); //This loads the texture from said location

	GLenum format; //This makes it where if a file does not have a alpha values, those values will not be loaded. 
	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3) {
		std::cout << "There are NO slpha values inside of " << fileName << "!" << std::endl;
		format = GL_RGB;
	}
	else if (nrChannels == 4) {
		std::cout << "There are slpha values inside of " << fileName << "!" << std::endl;
		format = GL_RGBA;
	}
	int channelNum = nrChannels; //Since stbi will load a null alpha field for PNG files without alpha values, we must find out if a file has alpha values
	texture = stbi_load(filePath.c_str(), &width, &height, &nrChannels, channelNum); //reload the image with the correct number of channels... 
	
	if (texture) { //meaning if that texture is not null 

				   //std::vector<unsigned char> holder(texture, texture + (width * height * nrChannels));

				   //std::cout << "FIRST STEP - FILE " << fileName << " SIZE: " << sizeofTexture << std::endl;
				   //std::cout << "holder has " << (int)holder[0] << ", " << (int)holder[1] << ", " << (int)holder[2] << std::endl;

		return TextureData(texture, width, height, format, nrChannels); //create the object 
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
		glfwTerminate();
		stbi_image_free(texture);
		exit(EXIT_FAILURE);
	}
}

//This method takes in an array of strings (the names of the cube map textures) and loads them into a cube map
int Loader::loadCubeMap(std::vector<std::string> textureFiles) {

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for (int i = 0; i<textureFiles.size(); i++) {
		//std::cout << "The following loadCubeMap textureFile is being loaded: " << textureFiles[i] << std::endl;
		TextureData data = processTexture(textureFiles[i]);


		//std::cout << "SECOND STEP - FILE " << textureFiles[i] << " SIZE: " << sizeofTexture << std::endl;

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, data.getFormat(), data.getWidth(),
			data.getHeight(), 0, data.getFormat(), GL_UNSIGNED_BYTE, &data.getTexture()[0]); //rgba throws an error with these textures since there are no alpha values in some textures... 

	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //makes the texture appear smooth
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //makes the texture appear smooth
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //prevents seams from showing 
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //prevents seams from showing 
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); //prevents seams from showing 
																			   //std::cout << "The textureID from loadCubeMap is: " << textureID << std::endl;
	return textureID;
}

int Loader::loadTexture(std::string fileName, float bias) {

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	int width, height, nrChannels;
	//stbi_set_flip_vertically_on_load(true); //This flips the image. might be needed sometimes
	getPaths getPath; //lets get the path of the texture. right now this assumes it is in the 'res' folder. 
	std::string filePath = getPath.GetCurrentWorkingDir() + "\\res\\" + fileName;
	//std::cout << "Filename inside of loadTexture is " << filePath << std::endl;
	unsigned char *texture = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 4); //This loads the texture from said location

	GLenum format; //This makes it where if a file does not have a alpha values, those values will not be loaded. 
	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3) {
		std::cout << "There are NO slpha values inside of " << fileName << "!" << std::endl;
		format = GL_RGB;
	}
	else if (nrChannels == 4) {
		std::cout << "There are alpha values inside of " << fileName << "!" << std::endl;
		format = GL_RGBA;
	}
	int channelNum = nrChannels; //Since stbi will load a null alpha field for PNG files without alpha values, we must find out if a file has alpha values
	texture = stbi_load(filePath.c_str(), &width, &height, &nrChannels, channelNum); //reload the image with the correct number of channels... 

	std::vector<unsigned char> testTexture(texture, texture + (width * height * nrChannels));

	if (texture) { //meaning if that texture is not null 
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, &testTexture[0]);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, bias);
		stbi_image_free(texture);
		std::cout << "The textureID from loadTexture is: " << textureID << std::endl;
		return textureID;
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
		glfwTerminate();
		stbi_image_free(texture);
		return -1;
	}

}

//Store the VBO data into the VAO (attribute list) - aka the meat of this code honestly 
void Loader::storeDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<float> data) {

	unsigned int vboID;
	glGenBuffers(1, &vboID);
	//Add the ID of the new VBO into our vector list
	vbos.push_back(vboID);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glBufferData(GL_ARRAY_BUFFER, data.size() * 4, &data[0], GL_STATIC_DRAW);  //static because we are not going to edit that data once its stored in the VBO

	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, 0);
	//number of the attrib list you are storing it in, length of each data set, type of data, is the data normalized, the distance between each of the vertices, and the offset

	//Now unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}


//The following binds the INDICES - which is why you need to use a GL_ELEMENT_ARRAY_BUFFER... 
void Loader::bindIndicesBuffer(std::vector<unsigned int> indices) {
	//std::cout << "The data of indices in bindIndicesBuffer (first three) is " << indices[0] << ", " << indices[1] << ", " << indices[2] << ", " << indices[3] << ", " << indices[4] << ", " << indices[5] << std::endl;
	//std::cout << "In the Loader::bindIndicesBuffer, the sizeof(indices) is " << indices.size() << std::endl;

	unsigned int vboID;
	glGenBuffers(1, &vboID);

	//Add the ID of the new VBO into our vector list
	vbos.push_back(vboID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);

	//Again, he implements a buffer class in order to manage and flip the buffer. 
	//But yet, the opengl website just passes the indices into the function directly... which is correct? 

	//cout << "bindINcides sizeof(incides) = " << indicesSize << endl;

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * 4, &indices[0], GL_STATIC_DRAW);

}


void Loader::unbindVAO() {

	glBindVertexArray(0); //just telling it to bind nothing.. so its being unbound.. 

}

//The following will clean up the vaos and vbos
void Loader::cleanUp() {

}

Loader::~Loader(void) {
}

