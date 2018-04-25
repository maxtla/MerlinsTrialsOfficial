#include "WallModelManager.h"

WallModelManager::WallModelManager()
{
}

WallModelManager::~WallModelManager()
{
}

void WallModelManager::createModels()
{
	for (auto var : this->geometry)
	{
		if (var->getName() == WALLO)
		{
			this->oWalls.push_back(WallModel(var));
		}
		else if(var->getName() == WALL)
		{
			this->walls.push_back(WallModel(var));
		}

		//add more wall types if needed

	}
}

void WallModelManager::initialize(std::vector<Geometry*> in_var)
{
	this->geometry = in_var;
}
