#include "stdafx.h"
#include "LevelOne.h"

LevelOne::LevelOne()
{
	this->device = nullptr;
}

LevelOne::~LevelOne()
{
}

void LevelOne::DrawLevel()
{
	this->staticManager.Draw();
	this->dynamicManager.Draw();
}

void LevelOne::collisionCheck()
{
	//check 
	if (1)
	{
		//handle

	}

	
}

bool LevelOne::initialize(std::vector<Geometry*> in_geometryVec, ID3D11Device* in_device, ID3D11DeviceContext* in_context, Camera* in_camera)
{

	this->dynamicManager.initialize(in_geometryVec, in_camera, in_device, in_context);
	this->staticManager.initialize(in_geometryVec, in_camera, in_device, in_context);


	return true;
}

