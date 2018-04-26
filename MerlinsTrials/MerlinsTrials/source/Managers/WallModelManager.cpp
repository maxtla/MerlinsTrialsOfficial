#include "WallModelManager.h"

WallModelManager::WallModelManager()
{
}

WallModelManager::WallModelManager(Camera* in_camera, ID3D11Device * in_device, ID3D11DeviceContext * in_context)
{
	this->camera = in_camera;
	this->device = in_device;
	this->context = in_context;
}

WallModelManager::~WallModelManager()
{
}

void WallModelManager::createModels(std::vector<Geometry*> in_geometryVec)
{
	for (auto var : in_geometryVec)
	{
		std::string name = var->getName();

		auto pos = name.find("_");
		if (pos == std::string::npos)
		{
			exit(-1);
		}

		name = name.substr(0, pos - 1);
		if (var->getName() == WALLO)
		{
			this->oWalls.push_back(WallModel(var, this->context));
		}
		else if(var->getName() == WALL)
		{
			this->walls.push_back(WallModel(var, this->context));
		}

		//add more wall type checks - Brick, wooden etc.

	}
}

void WallModelManager::update(const Dimension &in_dim)
{
	this->current_dim = in_dim;

}

void WallModelManager::Draw()
{
	//setshaders
	//cullcheck

	switch (this->current_dim)
	{
	case Dimension::NORMAL:
		for (auto var : this->walls)
		{
			var.Draw();
		}
		for (auto var : this->oWalls)
		{
			var.Draw();
		}
		break;
	case Dimension::OTHER:
		for (auto var : this->oWalls)
		{
			var.Draw();
		}		
		break;
	}

}

void WallModelManager::initialize(std::vector<Geometry*> in_geometryVec)
{
	this->createModels(in_geometryVec);
}
