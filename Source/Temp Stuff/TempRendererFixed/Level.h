#ifndef LEVEL_H
#define LEVEL_H
#include"ObjectImporter.h"
#include"Object.h"
#include<string>

using namespace DirectX::SimpleMath;

class Level
{
public:

	std::vector<Object> objects;

private:

	ObjectImporter* objImporter;
	std::string fileName;

public:

	Level();
	~Level();

	bool initialize(ID3D11Device * in_device, ObjectImporter * importer);
	std::vector<Object>* getObjects();

};

#endif // !LEVEL_H
