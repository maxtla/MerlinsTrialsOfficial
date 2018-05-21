#include "stdafx.h"
#include "MeshManager.h"


MeshManager::MeshManager()
{
}


MeshManager::~MeshManager()
{
	delete pObjectImporter;
	for (size_t i = 0; i < m_Walls.size(); i++)
	{
		for (size_t j = 0; j < m_Walls[i].size(); j++)
		{
			delete m_Walls[i][j];
			m_Walls[i][j] = nullptr;
		}
	}
	for (size_t i = 0; i < m_StaticLevels.size(); i++)
	{
		for (size_t j = 0; j < m_StaticLevels[i].size(); j++)
		{
			delete m_StaticLevels[i][j];
			m_StaticLevels[i][j] = nullptr;
		}
	}
}

void MeshManager::flush()
{
	for (size_t i = 0; i < m_Walls.size(); i++)
	{
		for (size_t j = 0; j < m_Walls[i].size(); j++)
		{
			delete m_Walls[i][j];
			m_Walls[i][j] = nullptr;
		}
		m_Walls[i].clear();
	}
	for (size_t i = 0; i < m_StaticLevels.size(); i++)
	{
		for (size_t j = 0; j < m_StaticLevels[i].size(); j++)
		{
			delete m_StaticLevels[i][j];
			m_StaticLevels[i][j] = nullptr;
		}
		m_StaticLevels[i].clear();
	}

	m_Walls.clear();
	m_StaticLevels.clear();
	m_TerrainVectorPoints.clear();
	m_TerrainIndices.clear();
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
	if (!loadStaticLevels())
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

bool MeshManager::loadStaticLevels()
{
	//hard coded stuff all here baby
	size_t index;
	//start with some walls 
	m_StaticLevels.resize(NR_OF_LEVELS);
	m_TerrainVectorPoints.resize(NR_OF_LEVELS);
	std::string pathAndIndex[] = { LEVEL_ONE };
	index = size_t(std::stoi(pathAndIndex[1]));

	if (!pObjectImporter->importLevel(pathAndIndex[0], m_StaticLevels[index], pDev, pDevCon))
		return false;

	//vector is filled now get all terrain meshes
	for (size_t i = 0; i < m_StaticLevels[index].size(); i++)
	{
		if (m_StaticLevels[index][i]->isTerrain)
		{
			m_TerrainVectorPoints[index].push_back(m_StaticLevels[index][i]->getTerrainPoints());
			//m_TerrainIndices[index].push_back(m_StaticLevels[index][i]->indices);
		}
	}

	return true;
}
