#ifndef LEVEL_H
#define LEVEL_H
#include"ObjectImporter.h"
#include"Geometry.h"
#include<string>
#include"Enumerators.h"
#include"WallModel.h"

using namespace DirectX::SimpleMath;

class Level
{
public:

	std::vector<Geometry> geometryVec;
	std::vector<WallModel> models;
private:

	ObjectImporter* objImporter;
	std::string fileName;

	std::vector<std::string> meshNames;


	sunType currentSun;
	sunType normalSun;
	sunType otherSun;
	

	void createModels();
public:

	Level();
	~Level();

	bool initialize(ID3D11Device * in_device, ObjectImporter * importer, const std::string &in_fileName);
	std::vector<Geometry>* getGeometryVec();

};

#endif // !LEVEL_H
