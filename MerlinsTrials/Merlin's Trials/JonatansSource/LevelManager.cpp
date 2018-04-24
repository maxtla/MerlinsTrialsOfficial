#include "LevelManager.h"

#define PATH_ONE "TestTri.obj"

#define NUM_OF_LEVELS 1

LevelManager::LevelManager()
{
	this->cLevel = 0;
}

LevelManager::~LevelManager()
{
	
}

bool LevelManager::initLevelManager(ID3D11Device * in_device, ID3D11DeviceContext * in_deviceContext, ObjectImporter * in_importer, Player* player)
{
	bool rValue = false;
	this->device = in_device;
	this->deviceContext = in_deviceContext;
	this->importer = in_importer;

	rValue = this->levelOne.initialize(in_device, in_deviceContext, this->importer, PATH_ONE, player);

	return rValue;
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
	switch (this->levelOne.getCurrentDimension())
	{
	case NORMAL:
	{
		this->levelOne.setDimension(Dimension::OTHER);
		break;
	}
	case OTHER:
	{
		this->levelOne.setDimension(Dimension::NORMAL);
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
