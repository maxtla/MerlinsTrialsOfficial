#include "LevelManager.h"

#define PATH_ONE "TestTri.obj"
#define PATH_TWO ""
#define PATH_THREE ""

#define NUM_OF_LEVELS 1

LevelManager::LevelManager()
{
	//initiate level vector
	this->levelVec.reserve(NUM_OF_LEVELS);
	this->filePathOrderVec.reserve(NUM_OF_LEVELS);
	for (UINT32 i = 0; i < NUM_OF_LEVELS; i++)
	{
		this->levelVec.push_back(Level());
	}
	//add filepath in order to appear
	this->filePathOrderVec.push_back(PATH_ONE);

	this->cDimension = Dimension::NORMAL;
	this->cLevel = 0;

}

LevelManager::~LevelManager()
{
	
}

void LevelManager::updateCurrentLevel()
{
	this->levelVec[this->cLevel];
}

bool LevelManager::initiateLevels()
{
	bool rValue = false;

	for (UINT32 i = 0; i < NUM_OF_LEVELS; i++)
	{
		rValue = this->levelVec[i].initialize(this->device, this->importer, this->filePathOrderVec[i]);
		if (!rValue)
		{
			return false;
		}
	}

	return true;
}

bool LevelManager::initLevelManager(ID3D11Device * in_device, ID3D11DeviceContext * in_deviceContext, ObjectImporter * in_importer)
{
	bool rValue = false;
	this->device = in_device;
	this->deviceContext = in_deviceContext;
	this->importer = in_importer;

	rValue = this->initiateLevels();

	return rValue;
}

void LevelManager::callSwapDimension()
{
	//swap current dimension use
	switch (cDimension)
	{
	case NORMAL:
	{
		this->cDimension = Dimension::OTHER;
		break;
	}
	case OTHER:
	{
		this->cDimension = Dimension::NORMAL;
		break;
	}
	}

}

void LevelManager::loadNextLevel()
{
	//increment indx to next level
	this->cLevel++;

}

unsigned int LevelManager::getNumOfLevels() const
{
	return NUM_OF_LEVELS;
}
