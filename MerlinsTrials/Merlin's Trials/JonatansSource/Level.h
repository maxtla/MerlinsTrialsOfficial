#ifndef LEVEL_H
#define LEVEL_H
#include"ObjectImporter.h"
#include"Geometry.h"
#include<string>
#include"Enumerators.h"
#include"WallModel.h"
#include"TerrainModel.h"
#include"Player.h"


class Level
{
public:
	std::vector<Geometry> geometryVec;
	std::vector<TerrainModel> terrainModels;
	std::vector<WallModel> wallModels;
	std::vector<ModelBase> miscModels;

private:
	ObjectImporter* objImporter;
	std::string fileName;
	ID3D11Device* device;
	
	Player* player;

	void createModel(const std::string &meshName, const int &i);

protected:
	sunType currentSun;
	sunType normalSun;
	sunType otherSun;

public:
	Level();
	~Level();

	bool collisionCheck();
	bool initialize(ID3D11Device * in_device, ObjectImporter * importer, const std::string &in_fileName);
	bool initializeModels();
};

#endif // !LEVEL_H
