#pragma once
class ParticleTexture
{
private:
	int textureID;
	int numberOfRows;
	bool additive;

public:
	ParticleTexture(int textureID, int numberOfRows, bool additive);

	int getTextureID();
	int getNumberOfRows();
	bool usesAdditiveBlending();
};

