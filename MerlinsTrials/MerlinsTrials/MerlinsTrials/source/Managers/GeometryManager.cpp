#include "stdafx.h"
#include "GeometryManager.h"


GeometryManager::GeometryManager()
{
}


GeometryManager::~GeometryManager()
{
	delete pObjectImporter;
}

void GeometryManager::initialize()
{
	pObjectImporter = new ObjectImporter();
}

bool GeometryManager::loadAllGeometry()
{
	if (!loadWalls())
		return false;

	return true;
}

bool GeometryManager::loadWalls()
{
	//hard coded stuff all here baby
	std::string pathAndIndex[2];
	size_t index;
	//start with some walls 
	m_Walls.reserve(NR_OF_WALL_MODELS);
	pathAndIndex[] = { BRICKWALL };
	index = size_t(std::stoi(pathAndIndex[1]));

	if (!pObjectImporter->importOBJModel(pathAndIndex[0], m_Walls[index]))
		return false;

	return true;
}

bool GeometryManager::loadStaticLevel()
{
	return false;
}
