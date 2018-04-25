#include "StaticModelManager.h"

StaticModelManager::StaticModelManager()
{
}

StaticModelManager::StaticModelManager(Player* in_player, ID3D11Device* in_device, ID3D11DeviceContext * in_context) : ManagerBase(in_player, in_device, in_context)
{
}

StaticModelManager::~StaticModelManager()
{
}

void StaticModelManager::rebindCB()
{

}

void StaticModelManager::createModels()
{
	for (auto var : this->geometry)
	{
		std::string name = var->getName();

		auto pos = name.find("_");
		if (pos == std::string::npos)
		{
			exit(-1); //haywire
		}

		name = name.substr(0, pos - 1);
		if (name == "Terrain")
		{
			this->terrianModels.push_back(TerrainModel(var));
		}
		else if (name == "Trunk")
		{
			this->trunkModels.push_back(TrunkModel(var));
		}
		else if (name == "Leaves")
		{
			this->leavesModels.push_back(LeavesModel(var));
		}
	}
}


void StaticModelManager::DrawModels()
{

}

void StaticModelManager::initialize(std::vector<Geometry*> in_var)
{
	this->geometry = in_var;
	this->createModels();
}
