#include "NormalMappedObjLoader.h"


NormalMappedObjLoader::NormalMappedObjLoader(void) {}

RawModel NormalMappedObjLoader::loadObj(std::string objFileName, Loader loader) {
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
			vertices.push_back(new VertexNM(vertices.size(), glm::vec3(vertexHolder[0], vertexHolder[1], vertexHolder[2])));
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
			//std::cout << "Looking at the following faces (so 9 elements)" << std::endl;
			//std::cout << faces[i * 9] << "/" << faces[i * 9 + 1] << "/" << faces[i * 9 + 2] << std::endl;
			//std::cout << faces[i * 9 + 3] << "/" << faces[i * 9 + 4] << "/" << faces[i * 9 + 5] << std::endl;
			//std::cout << faces[i * 9 + 6] << "/" << faces[i * 9 + 7] << "/" << faces[i * 9 + 8] << std::endl;

			//Current face is a single part of the 3 element face - VERTICE, TEXTURE, NORMAL
			glm::vec3 vertex0 = glm::vec3(faces[i * 3], faces[i * 3 + 1], faces[i * 3 + 2]);
			glm::vec3 vertex1 = glm::vec3(faces[i * 3 + 3], faces[i * 3 + 4], faces[i * 3 + 5]);
			glm::vec3 vertex2 = glm::vec3(faces[i * 3 + 6], faces[i * 3 + 7], faces[i * 3 + 8]);
			//std::cout << "Vertex0 = " << faces[i * 3] << "/" << faces[i * 3 + 1] << "/" << faces[i * 3 + 2] << std::endl;
			//std::cout << "Vertex1 = " << faces[i * 3 + 3] << "/" << faces[i * 3 + 4] << "/" << faces[i * 3 + 5] << std::endl;
			//std::cout << "Vertex2 = " << faces[i * 3 + 6] << "/" << faces[i * 3 + 7] << "/" << faces[i * 3 + 8] << std::endl;
			//VertexNM* v0 = processVertex(vertex0, vertices, &indices);
			//VertexNM* v1 = processVertex(vertex1, vertices, &indices);
			//VertexNM* v2 = processVertex(vertex2, vertices, &indices);

			VertexNM* v0 = processVertex(vertex0);
			VertexNM* v1 = processVertex(vertex1);
			VertexNM* v2 = processVertex(vertex2);

			//calculateTangents(v0, v1, v2, vertices, textures);
			calculateTangents(v0, v1, v2, textures);
			//std::cout << "The tangent for index " << index0 << ", " << index1 << ", and " << index2 << " = " << vertices[index0]->getAverageTangent().x << "/" << vertices[index0]->getAverageTangent().y << "/" << vertices[index0]->getAverageTangent().z << std::endl;
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

	std::ofstream outputfile; // this is to print out all the indices to see the instructions being fed. 
	
	/*
	outputfile.open("10202019testing.txt");
	if (objFileName == "cyborg.obj") {

		for (int x = 0; x < indices.size(); x = x + 1) {
			//std::cout << "x = " << x << std::endl;
			//std::cout << "indices.size = " << indices.size() << std::endl;
			outputfile << "Indice - (element " << x << ") " << indices[x] << "\n";
			outputfile << "      Vertex Position  :  " << finalVertices[indices[x] * 3] << "/" << finalVertices[indices[x] * 3 + 1] << "/" << finalVertices[indices[x] * 3 + 2] << "\n";
			outputfile << "      Texture Coord    : " << finalTextures[indices[x] * 2] << "/" << finalTextures[indices[x] * 2 + 1] << "\n";
			outputfile << "      Normal Vector    : " << finalNormals[indices[x] * 3] << "/" << finalNormals[indices[x] * 3 + 1] << "/" << finalNormals[indices[x] * 3 + 2] << "\n";
			outputfile << "      Tangent          : " << finalTangents[indices[x] * 3] << "/" << finalTangents[indices[x] * 3 + 1] << "/" << finalTangents[indices[x] * 3 + 2] << "\n\n";
		}

	}
	outputfile.close();*/


	RawModel raw = loader.loadToVAO(finalVertices, finalTextures, finalNormals, finalTangents, indices);
	finalVertices.clear();
	finalTextures.clear();
	finalNormals.clear();
	finalTangents.clear();
	vertices.clear();
	indices.clear();

	return raw;
}

void NormalMappedObjLoader::calculateTangents(VertexNM* v0, VertexNM* v1, VertexNM* v2, std::vector<glm::vec2> textures) {
//void NormalMappedObjLoader::calculateTangents(VertexNM* v0, VertexNM* v1, VertexNM* v2, std::vector<VertexNM*> vertices, std::vector<glm::vec2> textures) {

	//std::cout << "v0 vertex's position: " << v0->getPosition().x << "/" << v0->getPosition().y << "/" << v0->getPosition().z << std::endl;
	//std::cout << "v1 vertex's position: " << v1->getPosition().x << "/" << v1->getPosition().y << "/" << v1->getPosition().z << std::endl;
	//std::cout << "v2 vertex's position: " << v2->getPosition().x << "/" << v2->getPosition().y << "/" << v2->getPosition().z << std::endl;

	glm::vec3 deltaPos1 = v1->getPosition() - v0->getPosition();
	glm::vec3 deltaPos2 = v2->getPosition() - v0->getPosition();
	//std::cout << "DeltaPos1 = " << deltaPos1.x << "/" << deltaPos1.y << "/" << deltaPos1.z <<
		//"\nDeltaPos2 = " << deltaPos2.x << "/" << deltaPos2.y << "/" << deltaPos2.z << std::endl;
	glm::vec2 uv0 = textures[v0->getTextureIndex()];
	glm::vec2 uv1 = textures[v1->getTextureIndex()];
	glm::vec2 uv2 = textures[v2->getTextureIndex()];
	glm::vec2 deltaUv1 = uv1 - uv0;
	glm::vec2 deltaUv2 = uv2 - uv0;

	//std::cout << "uv0 = " << uv0.x << " " << uv0.y << std::endl;
	//std::cout << "uv1 = " << uv1.x << " " << uv1.y << std::endl;
	//std::cout << "uv2 = " << uv2.x << " " << uv2.y << std::endl;
	//std::cout << "DeltaUV1 = " << deltaUv1.x << "/" << deltaUv1.y << std::endl;
	//std::cout << "deltaUv2 = " << deltaUv2.x << "/" << deltaUv2.y << std::endl;

	float r = 1.0f / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x);
	//std::cout << "r = " << r << std::endl;

	deltaPos1 = deltaPos1 * deltaUv2.y;
	deltaPos2 = deltaPos2 * deltaUv1.y;
	//std::cout << "After Scaling: deltaPos1 = " << deltaPos1.x << "/" << deltaPos1.y << "/" << deltaPos1.z <<
		//"\ndeltaPos2 = " << deltaPos2.x << "/" << deltaPos2.y << "/" << deltaPos2.z << std::endl;
	
	glm::vec3 tangent = deltaPos1 - deltaPos2;
	//std::cout << "Tangent before scaling = " << tangent.x << "/" << tangent.y << "/" << tangent.z << std::endl;
	tangent = tangent * r;
	//std::cout << "Tangent after scaling = " << tangent.x << "/" << tangent.y << "/" << tangent.z << std::endl;
	
	v0->addTangent(tangent);
	v1->addTangent(tangent);
	v2->addTangent(tangent);

}
 
//VertexNM* NormalMappedObjLoader::processVertex(glm::vec3 currentFacePart, std::vector<VertexNM*> vertices, std::vector<unsigned int>* indices) {
VertexNM* NormalMappedObjLoader::processVertex(glm::vec3 currentFacePart) {
	int index = currentFacePart.x - 1;                                        //Get the first element of the face triage (which is the vertex index)
	//std::cout << "indice: " << index << std::endl;
	//std::cout << "Current face: " << currentFacePart.x << "/ " << currentFacePart.y << "/ " << currentFacePart.z << std::endl;
	VertexNM* currentVertex = vertices[index];
	//std::cout << "The current vertex is : X: " << currentVertex->getPosition().x << " Y: " << currentVertex->getPosition().y <<
		//" Z: " << currentVertex->getPosition().z << std::endl;
	//std::cout << "Current vertex texture = " << currentVertex->getTextureIndex() << " normal = " << currentVertex->getNormalIndex() << std::endl;
	int textureIndex = currentFacePart.y - 1;                                 //Get the second element of the face part
	int normalIndex = currentFacePart.z - 1;                                  //Get the third elemtn of the face part
	if (!currentVertex->isSet()) {
		//std::cout << "Setting currentVertex " << currentVertex->getPosition().x << "/" << currentVertex->getPosition().y << "/" << currentVertex->getPosition().z <<
			//" to have textureIndex : " << textureIndex << " and normalIndex " << normalIndex << std::endl;
		currentVertex->setTextureIndex(textureIndex);
		currentVertex->setNormalIndex(normalIndex);
		indices.push_back(index);
		return currentVertex;
	}
	else {
		//currentVertex->setTextureIndex(textureIndex);
		//currentVertex->setNormalIndex(normalIndex);
		//indices->push_back(index);
		//return currentVertex;
		//return dealWithAlreadyProcessedVertex(currentVertex, textureIndex, normalIndex, indices, vertices);
		return dealWithAlreadyProcessedVertex(currentVertex, textureIndex, normalIndex);
	}
}
VertexNM* NormalMappedObjLoader::dealWithAlreadyProcessedVertex(VertexNM* previousVertex, int newTextureIndex, int newNormalIndex) {
//VertexNM* NormalMappedObjLoader::dealWithAlreadyProcessedVertex(VertexNM* previousVertex, int newTextureIndex, int newNormalIndex,
	//std::vector<unsigned int>* indices, std::vector<VertexNM*> vertices) {
	//std::cout << "Deal with already processed vertex called!" << std::endl;
	//std::cout << "Parameters - previousVertex = " << previousVertex->getIndex() <<
		//"\n newTextureIndex = " << newTextureIndex << "\n newNormalIndex = " << newNormalIndex << std::endl;
	if (previousVertex->hasSameTextureAndNormal(newTextureIndex, newNormalIndex)) {
		indices.push_back(previousVertex->getIndex());
		return previousVertex;
	}
	else {
		VertexNM* anotherVertex = previousVertex->getDuplicateVertex();
		if (anotherVertex != NULL) {
			return dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex, newNormalIndex);
		}
		else {
			VertexNM* duplicateVertex = new VertexNM(vertices.size(), previousVertex->getPosition());
			duplicateVertex->setTextureIndex(newTextureIndex);
			duplicateVertex->setNormalIndex(newNormalIndex);
			previousVertex->setDuplicateVertex(duplicateVertex);
			vertices.push_back(duplicateVertex);
			indices.push_back(duplicateVertex->getIndex());
			return duplicateVertex;
		}
	}
}

void NormalMappedObjLoader::removeUnusedVertices(std::vector<VertexNM*> vertices) {
	for (unsigned int i = 0; i < vertices.size(); i = i + 1) {
		vertices[i]->averageTangents();
		if (!vertices[i]->isSet()) { //If the vertex doesnt have a textureIndex or normalIndex then..
			vertices[i]->setTextureIndex(0);
			vertices[i]->setNormalIndex(0);
		}
	}
}

float NormalMappedObjLoader::convertDataToArrays(std::vector<VertexNM*> vertices, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals) {
	float furthestPoint = 0;	
	for (int i = 0; i < vertices.size(); i++) {
		VertexNM* currentVertex = vertices[i];
		if (currentVertex->getLength() > furthestPoint) {
			furthestPoint = currentVertex->getLength();
		}
		glm::vec3 position = currentVertex->getPosition();
		glm::vec2 textureCoord = textures[currentVertex->getTextureIndex()];
		glm::vec3 normalVector = normals[currentVertex->getNormalIndex()];
		glm::vec3 tangent = currentVertex->getAverageTangent();
		finalVertices.push_back(position.x);
		finalVertices.push_back(position.y);
		finalVertices.push_back(position.z);
		finalTextures.push_back(textureCoord.x);
		finalTextures.push_back(1 - textureCoord.y);
		finalNormals.push_back(normalVector.x);
		finalNormals.push_back(normalVector.y);
		finalNormals.push_back(normalVector.z);
		finalTangents.push_back(tangent.x);
		finalTangents.push_back(tangent.y);
		finalTangents.push_back(tangent.z);

	}
	return furthestPoint;
}

NormalMappedObjLoader::~NormalMappedObjLoader() {}
