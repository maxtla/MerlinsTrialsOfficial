#include "stdafx.h"
#include "LevelOne.h"

LevelOne::LevelOne()
{
	this->device = nullptr;
}

LevelOne::~LevelOne()
{
}

void LevelOne::checkDim()
{
	//if key is pressed
	if (this->input_handler->dimensionCheck())
	{
		//check timer on dimension change, 1sec
		if (this->timer.checkDT(1.0f))
		{
			//normal = 0, Other = 1
			if (this->current_dim)
			{
				this->current_dim = Dimension::NORMAL;
			}
			else
			{
				this->current_dim = Dimension::OTHER;
			}

			this->timer.startTimer();
		}
	}
}

void LevelOne::DrawLevel()
{
	this->staticManager.Draw();
	this->dynamicManager.Draw();
}

void LevelOne::update()
{
	this->checkDim();
	this->dynamicManager.update(this->current_dim);
	this->staticManager.update(this->current_dim);
}

void LevelOne::collisionCheck()
{
	//check 
	if (1)
	{
		//handle

	}

	
}

bool LevelOne::initialize(std::vector<Geometry*> in_geometryVec, ID3D11Device* in_device, ID3D11DeviceContext* in_context, Player* in_player, InputHandler* in_handler)
{
	this->input_handler = in_handler;
	this->dynamicManager.initialize(in_geometryVec, in_player, in_device, in_context);
	this->staticManager.initialize(in_geometryVec, in_player->getCamera(), in_device, in_context);

	return true;
}

