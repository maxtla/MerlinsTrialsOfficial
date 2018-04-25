#ifndef LEVEL_H
#define LEVEL_H
#include "..\Importer\ObjectImporter.h"
#include<string>

using namespace DirectX::SimpleMath;

class Level
{
public:

	std::vector<Geometry> objects;

private:

	ObjectImporter* objImporter;
	std::string fileName;

public:

	Level();
	~Level();

	bool initialize(ID3D11Device * in_device, ObjectImporter * importer);
	std::vector<Geometry>* getGeometry();
	int findObject(std::string name);

};

#endif // !LEVEL_H
