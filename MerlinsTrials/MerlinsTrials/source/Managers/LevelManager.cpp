#include "stdafx.h"
#include "LevelManager.h"



#define NUM_OF_LEVELS 1

LevelManager::LevelManager()
{
	this->cDimension = Dimension::NORMAL;
	this->cLevel = 0;
}

LevelManager::~LevelManager()
{
	
}

void LevelManager::initialize(ID3D11Device * in_device, ID3D11DeviceContext * in_deviceContext, InputHandler* in_handler, Player* in_player)
{
	this->device = in_device;
	this->deviceContext = in_deviceContext;
	this->inputHandler = in_handler;

	this->levelOne.initialize(in_device, in_deviceContext, in_player);

}

void LevelManager::update()
{
	//other stuff
	this->dimensionCheck();
	this->levelOne.update(this->cDimension);
	this->levelOne.Draw();

}

void LevelManager::changeLevel()
{
	this->cLevel++;
}

void LevelManager::dimensionCheck()
{
	//swap current dimension use
	//if key is pressed
	if (this->inputHandler->dimensionCheck())
	{
		//check timer on dimension change, 1sec
		if (this->timer.checkDT(1.0f))
		{
			//normal = 0, Other = 1
			if (this->cDimension)
			{
				this->cDimension = Dimension::NORMAL;
			}
			else
			{
				this->cDimension = Dimension::OTHER;
			}

			this->timer.startTimer();
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
