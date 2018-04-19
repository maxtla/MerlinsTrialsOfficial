#ifndef LEVEL_H
#define LEVEL_H
#include"ObjectImporter.h"
#include"Geometry.h"
#include<string>
#include"Enumerators.h"
#include"WallModel.h"
#include"TerrainModel.h"

using namespace DirectX::SimpleMath;

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

	std::vector<std::string> meshNames;
	sunType currentSun;
	sunType normalSun;
	sunType otherSun;
	

	void createModel(const std::string &meshName, const int &i);
public:

	Level();
	~Level();

	bool initialize(ID3D11Device * in_device, ObjectImporter * importer, const std::string &in_fileName);
	std::vector<Geometry>* getGeometryVec();

};

#endif // !LEVEL_H
