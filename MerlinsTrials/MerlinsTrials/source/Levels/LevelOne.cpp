#include "stdafx.h"
#include "LevelOne.h"

LevelOne::LevelOne()
{
	this->device = nullptr;
}

LevelOne::~LevelOne()
{
}

void LevelOne::Draw()
{
	this->staticManager.Draw();
	this->dynamicManager.Draw();
}

void LevelOne::importLevel()
{
	//use whatever function, this->geometryVec for this specific level
	this->geometryManager.initialize();
	this->geometryManager.loadAllGeometry();
}

void LevelOne::update(const Dimension &in_dim)
{
	this->collisionCheck();
	this->dynamicManager.update(in_dim);
	this->staticManager.update(in_dim);
}

void LevelOne::collisionCheck()
{
	//check 
	if (1)
	{
		//handle

	}	
}

void LevelOne::initialize(ID3D11Device* in_device, ID3D11DeviceContext* in_context, Player* in_player)
{
	this->importLevel();
	this->dynamicManager.initialize(this->geometryVec, in_player, in_device, in_context);
	this->staticManager.initialize(this->geometryVec, in_player->getCamera(), in_device, in_context);

}

