#ifndef LEVEL_H
#define LEVEL_H
#include "..\Importer\ObjectImporter.h"
#include<string>

using namespace DirectX::SimpleMath;

class Level
{
public:

	std::vector<Mesh> objects;

private:

	ObjectImporter* objImporter;
	std::string fileName;

public:

	Level();
	~Level();

	bool initialize(ID3D11Device * in_device, ObjectImporter * importer);
	std::vector<Mesh>* getGeometry();
	int findObject(std::string name);

};

#endif // !LEVEL_H
