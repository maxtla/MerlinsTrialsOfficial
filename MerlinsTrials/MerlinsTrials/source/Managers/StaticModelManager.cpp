#include "StaticModelManager.h"

bool StaticModelManager::checkDim()
{	
	//if key is pressed
	if (this->input_handler->dimensionCheck())
	{
		//check timer on dimension change, 1sec
		if (this->timer.checkDT(1.0f))
		{	
			//normal = 0
			if (!this->current_dim)
			{
				this->current_dim = Dimension::OTHER;
			}
			else
			{
				this->current_dim = Dimension::NORMAL;
			}

			this->timer.startTimer();
		}
	}
}

StaticModelManager::StaticModelManager()
{
}

StaticModelManager::StaticModelManager(InputHandler* in_handler)
{
	this->input_handler = in_handler;
}

StaticModelManager::~StaticModelManager()
{
}

void StaticModelManager::update()
{
	this->checkDim();
}

void StaticModelManager::Draw()
{
	//check dimension and if managers are active

	this->wallManager.Draw(this->current_dim);
	//draw other managers

}

void StaticModelManager::initialize(std::vector<Geometry*> in_geometry, Camera* in_camera, ID3D11Device* in_device, ID3D11DeviceContext * in_context)
{	
	//initiate managers
	this->wallManager = WallModelManager(in_camera, in_device, in_context);
	this->wallManager.initialize(in_geometry);

	//add other managers
	//here
}
