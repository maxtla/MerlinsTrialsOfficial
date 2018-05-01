#include "stdafx.h"
#include "MeshManager.h"


MeshManager::MeshManager()
{
}


MeshManager::~MeshManager()
{
	delete pObjectImporter;
}

void MeshManager::initialize(ID3D11Device * pDev, ID3D11DeviceContext * pDevCon)
{
	pObjectImporter = new ObjectImporter();
	this->pDev = pDev;
	this->pDevCon = pDevCon;
}

bool MeshManager::loadAllGeometry()
{
	if (!loadWalls())
		return false;

	return true;
}

bool MeshManager::loadWalls()
{
	//hard coded stuff all here baby
	size_t index;
	//start with some walls 
	m_Walls.resize(NR_OF_WALL_MODELS);
	std::string pathAndIndex[] = { TESTWALL };
	index = size_t(std::stoi(pathAndIndex[1]));

	if (!pObjectImporter->importOBJModel(pathAndIndex[0], m_Walls[index], pDev, pDevCon))
		return false;

	return true;
}

bool MeshManager::loadStaticLevel()
{
	return false;
}
