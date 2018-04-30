#include "stdafx.h"
#include "LevelManager.h"

#define PATH_ONE "TestTri.obj"

#define NUM_OF_LEVELS 1

LevelManager::LevelManager()
{
	this->cDimension = Dimension::NORMAL;
	this->cLevel = 0;
}

LevelManager::~LevelManager()
{
	
}

bool LevelManager::initLevelManager(ID3D11Device * in_device, ID3D11DeviceContext * in_deviceContext, ObjectImporter * in_importer, Player* player)
{
	/*bool rValue = false;
	this->device = in_device;
	this->deviceContext = in_deviceContext;
	this->importer = in_importer;

	rValue = this->levelOne.initialize(this->device, this->importer, PATH_ONE, player);


	return rValue;*/
	return true;
}

void LevelManager::updateCurrentLevel()
{
	//other stuff
	this->levelOne.collisionCheck();
	this->levelOne.Draw();

}

void LevelManager::changeLevel()
{
	this->cLevel++;
}

void LevelManager::callSwapDimension()
{
	//swap current dimension use
	switch (cDimension)
	{
	case NORMAL:
	{
		this->cDimension = Dimension::OTHER;
		
		for (size_t i = 0; i < this->levelOne.wallModels.size(); i++)
		{
			this->levelOne.wallModels[i].setVisibility(false);
		}
		break;
	}
	case OTHER:
	{
		this->cDimension = Dimension::NORMAL;

		for (size_t i = 0; i < this->levelOne.wallModels.size(); i++)
		{
			this->levelOne.wallModels[i].setVisibility(true);
		}
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
