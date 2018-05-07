#include "stdafx.h"
#include "MeshManager.h"
#include<iostream>
#include<fstream>
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
	if (!loadWand())
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

bool MeshManager::loadWand() {

	//Vars to load wand
	this->m_Wand.resize(NR_OF_WANDS);
	std::string pI[] = { WAND_PATH };

	if (!pObjectImporter->importOBJModel(pI[0], m_Wand, pDev, pDevCon))
		return false;

	return true;

}

bool MeshManager::loadStaticLevels()
{
	//hard coded stuff all here baby
	size_t index;
	//start with some walls 
	m_StaticLevels.resize(NR_OF_LEVELS);
	std::string pathAndIndex[] = { LEVEL_ONE };
	index = size_t(std::stoi(pathAndIndex[1]));

	if (!pObjectImporter->importLevel(pathAndIndex[0], m_StaticLevels[index], pDev, pDevCon))
		return false;
	
	int nr = 0;
	//seperate pedestals
	for (size_t i = 0; i < m_StaticLevels.size(); i++)
	{
		for (size_t j = 0; j < m_StaticLevels[i].size(); j++)
		{
			if (m_StaticLevels[i][j]->getName() == "Pedestal")
			{
				m_pedestals.push_back(m_StaticLevels[i][j]);
				nr++;
			}
				
		}
	}
	return true;
}
