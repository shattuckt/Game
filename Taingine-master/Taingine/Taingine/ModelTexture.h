#pragma once
class ModelTexture
{
private:

	int textureID;
	int normalMap;

	float shineDamper;
	float reflectivity;
	bool hasTransparency;
	bool useFakeLighting;

	int numberOfRows;

public:
	ModelTexture(int texture);
	ModelTexture(int id, int normalMapID);
	ModelTexture();

	int getID();
	float getShineDamper();
	float getReflectivity();
	bool getHasTransparency();
	bool getuseFakeLighting();
	int getNumberofRows();
	void setNumberOfRows(int numberOfRow);

	int getNormalMap();
	void setNormalMap(int normalMaps);

	void setShineDamper(float shineDampers);
	void setReflectivity(float reflectivitys);
	void setHasTransparency(bool hasTransparencys);
	void setuseFakeLighting(bool useFakeLighting);

	~ModelTexture(void);

};

