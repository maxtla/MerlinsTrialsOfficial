#ifndef LEVELONE_H
#define LEVELONE_H
#include"ObjectImporter.h"
#include"Geometry.h"
#include<string>
#include"Enumerators.h"
#include"WallModel.h"
#include"TerrainModel.h"
#include"Player.h"
#include"Collision.h"

class LevelOne
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
	
	Collision collideManager;
	Player* player;

	void createModel(const std::string &meshName, const int &i);

public:
	LevelOne();
	~LevelOne();

	void collisionCheck();
	bool initialize(ID3D11Device * in_device, ObjectImporter * importer, const std::string &in_fileName);
	bool initializeModels();
};

#endif // !LEVELONE_H
