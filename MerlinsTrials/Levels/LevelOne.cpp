#include "stdafx.h"
#include "LevelOne.h"

LevelOne::LevelOne()
{
	this->device = nullptr;
}

LevelOne::~LevelOne()
{
	this->fileName.clear();
}

void LevelOne::DrawLevel()
{
	this->wallManager.DrawModels();
	this->staticManager.DrawModels();
}

void LevelOne::collisionCheck()
{
	//check 
	if (1)
	{
		//handle

	}

	
}

bool LevelOne::initialize(ID3D11Device* in_device, ID3D11DeviceContext* in_deviceContext, const std::string &in_fileName, Player* player)
{
	this->player = player;
	this->device = in_device;
	this->deviceContext = in_deviceContext;
	this->fileName = in_fileName;

	return true;
}

void LevelOne::initializeWallManager(std::vector<Geometry*> in_var)
{
	this->wallManager.initialize(in_var);
}

void LevelOne::initializeStaticManager(std::vector<Geometry*> in_var)
{
	this->staticManager.initialize(in_var);
}
