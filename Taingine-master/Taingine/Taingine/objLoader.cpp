#include "ObjLoader.h"

objLoader::objLoader(void) {}

RawModel objLoader::loadObj(std::string objFileName, Loader loader) {
	getPaths getPath; //lets get the path of the texture. right now this assumes it is in the 'res' folder. 
					  //std::string filePath = getPath.GetCurrentWorkingDir() + "\\res\\box.obj";
					  //std::string filePath = getPath.GetCurrentWorkingDir() + "\\res\\boulder.obj";
	std::string filePath = getPath.GetCurrentWorkingDir() + "\\res\\" + objFileName;

	std::cout << "The filepath extracted from getPaths is: " << filePath << std::endl;

	std::string line;                                                       //current line of text file
	std::ifstream fileReader(filePath);                                    //load the object file

	//std::vector<VertexNM *> vertices;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> faces;
	std::vector<unsigned int> debugFaces;
	std::vector<std::string> faceLine;
	std::vector<std::string>::iterator faceLineIterator;
	//std::vector<unsigned int> indices;

	//The following vectors are meant to just hold the segments of data on each line before being pushed into the main vectors as objects.
	std::vector<float> vertexHolder;
	std::vector<float> textureHolder;
	std::vector<float> normalHolder;
	std::vector<std::string> faceHolder;

	//The following is for the comparison operators in each section
	std::string vert = "v";
	std::string text = "vt";
	std::string norm = "vn";
	std::string face = "f";

	//The following will be used to obtain the first word out of each line
	std::string delimiter = " ";
	std::string secondDelimiter = "/";
	size_t pos = 0; //Used to break the line into sections by obtaining the size of each piece of string
	size_t secondPos = 0; //used to break the face segments apart.
	std::string dataType;
	int counter;
	int isEnd; //this is used to break out of the indices loop 
	double i;

	while (true) {
		getline(fileReader, line); //Get the line
		pos = line.find(delimiter);
		dataType = line.substr(0, pos);
		//std::cout << "Line: " << line << std::endl;
		if (dataType == vert) {
			line.erase(0, pos + delimiter.length());                                              //Rid of the ID ('v') 
			while ((pos = line.find(delimiter)) != std::string::npos) {
				vertexHolder.push_back(::atof(line.substr(0, pos).c_str()));					 //Add element to vector 
				line.erase(0, pos + delimiter.length());
			}
			vertexHolder.push_back(::atof(line.c_str()));                                        //Add last element to vector
			vertices.push_back(new Vertex(vertices.size(), glm::vec3(vertexHolder[0], vertexHolder[1], vertexHolder[2])));
			vertexHolder.clear();
		}
		else if (dataType == text) {
			line.erase(0, pos + delimiter.length());                                              //Rid of the ID ('v') 
			while ((pos = line.find(delimiter)) != std::string::npos) {
				textureHolder.push_back(::atof(line.substr(0, pos).c_str()));                      //Add element to vector 
				line.erase(0, pos + delimiter.length());
			}
			textureHolder.push_back(::atof(line.c_str()));                                        //Add last element to vector
			textures.push_back(glm::vec2(textureHolder[0], textureHolder[1]));                    //Add tx coords to textures vector.
			textureHolder.clear();
		}
		else if (dataType == norm) {
			line.erase(0, pos + delimiter.length());                                              //Rid of the ID ('v') 
			while ((pos = line.find(delimiter)) != std::string::npos) {
				normalHolder.push_back(::atof(line.substr(0, pos).c_str()));                       //Add element to vector 
				line.erase(0, pos + delimiter.length());
			}
			normalHolder.push_back(::atof(line.c_str()));                                        //Add last element to vector
			normals.push_back(glm::vec3(normalHolder[0], normalHolder[1], normalHolder[2]));    //Add normal to normals vector
			normalHolder.clear();
		}
		else if (dataType == face) {                                                              //Each face is a triangle
			break;
		}
	}

	while (!line.empty() && dataType == face) {          //********************* The following is to process the lines with 'f' which are the faces
		line.erase(0, pos + delimiter.length());                                              //Rid of the ID ('f') 
		while ((pos = line.find(delimiter)) != std::string::npos) {                           //Load up faceholder with all three xx/xx/xx face segments 
			faceHolder.push_back(line.substr(0, pos));
			line.erase(0, pos + delimiter.length());
		}
		faceHolder.push_back(line.c_str());

		for (i = 0; i < faceHolder.size(); i++) {                                            //Remove each int value from each segement (9 total ints) 
			while ((secondPos = faceHolder[i].find(secondDelimiter)) != std::string::npos) {
				faces.push_back(::atof(faceHolder[i].substr(0, secondPos).c_str()));                       //Add element to vector 
				faceHolder[i].erase(0, secondPos + secondDelimiter.length());
			}
			faces.push_back(::atof(faceHolder[i].c_str()));
			debugFaces.push_back(::atof(faceHolder[i].c_str()));
		}

		for (i = 0; i < faces.size() / 9; i++) {  		                                      //Process each 3 - vertex/texturecoords/normals
			glm::vec3 vertex0 = glm::vec3(faces[i * 3], faces[i * 3 + 1], faces[i * 3 + 2]);
			glm::vec3 vertex1 = glm::vec3(faces[i * 3 + 3], faces[i * 3 + 4], faces[i * 3 + 5]);
			glm::vec3 vertex2 = glm::vec3(faces[i * 3 + 6], faces[i * 3 + 7], faces[i * 3 + 8]);
			Vertex* v0 = processVertex(vertex0);
			Vertex* v1 = processVertex(vertex1);
			Vertex* v2 = processVertex(vertex2);
		}

		getline(fileReader, line);                                                               //Get next line
		pos = line.find(delimiter);
		dataType = line.substr(0, pos);
		faceHolder.clear();
		faces.clear();
	}
	fileReader.close();

	removeUnusedVertices(vertices);


	float furthest = convertDataToArrays(vertices, textures, normals);

	RawModel raw = loader.loadToVAO(finalVertices, finalTextures, finalNormals, indices);
	finalVertices.clear();
	finalTextures.clear();
	finalNormals.clear();
	vertices.clear();
	indices.clear();

	return raw;
}

//VertexNM* NormalMappedObjLoader::processVertex(glm::vec3 currentFacePart, std::vector<VertexNM*> vertices, std::vector<unsigned int>* indices) {
Vertex* objLoader::processVertex(glm::vec3 currentFacePart) {
	int index = currentFacePart.x - 1;                                        //Get the first element of the face triage (which is the vertex index)
	Vertex* currentVertex = vertices[index];
	int textureIndex = currentFacePart.y - 1;                                 //Get the second element of the face part
	int normalIndex = currentFacePart.z - 1;                                  //Get the third elemtn of the face part
	if (!currentVertex->isSet()) {
		currentVertex->setTextureIndex(textureIndex);
		currentVertex->setNormalIndex(normalIndex);
		indices.push_back(index);
		return currentVertex;
	}
	else {
		return dealWithAlreadyProcessedVertex(currentVertex, textureIndex, normalIndex);
	}
}

Vertex* objLoader::dealWithAlreadyProcessedVertex(Vertex* previousVertex, int newTextureIndex, int newNormalIndex) {
	if (previousVertex->hasSameTextureAndNormal(newTextureIndex, newNormalIndex)) {
		//std::cout << "This new vertex has the same texture and normal as the previously processed vertex" << std::endl;
		indices.push_back(previousVertex->getIndex());
		return previousVertex;
	}
	else {
		Vertex* anotherVertex = previousVertex->getDuplicateVertex();
		if (anotherVertex != NULL) {
			return dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex, newNormalIndex);
		}
		else {
			Vertex* duplicateVertex = new Vertex(vertices.size(), previousVertex->getPosition());
			duplicateVertex->setTextureIndex(newTextureIndex);
			duplicateVertex->setNormalIndex(newNormalIndex);
			previousVertex->setDuplicateVertex(duplicateVertex);
			vertices.push_back(duplicateVertex);
			indices.push_back(duplicateVertex->getIndex());
			return duplicateVertex;
		}
	}
}

void objLoader::removeUnusedVertices(std::vector<Vertex*> vertices) {
	for (unsigned int i = 0; i < vertices.size(); i = i + 1) {
		if (!vertices[i]->isSet()) { //If the vertex doesnt have a textureIndex or normalIndex then..
			vertices[i]->setTextureIndex(0);
			vertices[i]->setNormalIndex(0);
		}
	}
}

float objLoader::convertDataToArrays(std::vector<Vertex*> vertices, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals) {
	float furthestPoint = 0;
	for (int i = 0; i < vertices.size(); i++) {
		Vertex* currentVertex = vertices[i];
		if (currentVertex->getLength() > furthestPoint) {
			furthestPoint = currentVertex->getLength();
		}
		glm::vec3 position = currentVertex->getPosition();
		glm::vec2 textureCoord = textures[currentVertex->getTextureIndex()];
		glm::vec3 normalVector = normals[currentVertex->getNormalIndex()];
		finalVertices.push_back(position.x);
		finalVertices.push_back(position.y);
		finalVertices.push_back(position.z);
		finalTextures.push_back(textureCoord.x);
		finalTextures.push_back(1 - textureCoord.y);
		finalNormals.push_back(normalVector.x);
		finalNormals.push_back(normalVector.y);
		finalNormals.push_back(normalVector.z);

	}
	return furthestPoint;
}

objLoader::~objLoader() {}