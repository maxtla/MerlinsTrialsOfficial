#include "WallModelManager.h"

WallModelManager::WallModelManager()
{
}

WallModelManager::WallModelManager(Player * in_player, ID3D11Device * in_device, ID3D11DeviceContext * in_context) : ManagerBase(in_player, in_device, in_context)
{
	//initcomponent
	this->shaderComponent;
}

WallModelManager::~WallModelManager()
{
}

void WallModelManager::createModels()
{
	for (auto var : this->geometry)
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
			this->oWalls.push_back(WallModel(var));
		}
		else if(var->getName() == WALL)
		{
			this->walls.push_back(WallModel(var));
		}

		//add more wall types if needed

	}
}

void WallModelManager::DrawModels()
{

}

void WallModelManager::initialize(std::vector<Geometry*> in_var)
{
	this->geometry = in_var;
	this->createModels();
}
