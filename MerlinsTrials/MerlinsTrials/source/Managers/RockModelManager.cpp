#include "stdafx.h"
#include "RockModelManager.h"

RockModelManager::RockModelManager()
{
}

RockModelManager::RockModelManager(Camera * in_camera, ID3D11Device * in_device, ID3D11DeviceContext * in_context)
{
}

RockModelManager::~RockModelManager()
{
}

void RockModelManager::createShaders()
{
	//


}

void RockModelManager::createModels(std::vector<Geometry*> in_geometryVec)
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
		if (var->getName() == "Rocks") //change name to fit scene level
		{
			this->oRocks.push_back(RockModel(var, this->context));
		}
		if (var->getName() == "SmallRocks") //change name to fit scene level
		{
			this->sRocks.push_back(RockModel(var, this->context));
		}
	}
}

void RockModelManager::update(const Dimension & in_dim)
{
	this->current_dim = in_dim;
}

void RockModelManager::Draw()
{
	switch (this->current_dim)
	{
	case Dimension::NORMAL:
		break;
	case Dimension::OTHER:
		break;
	}
}

void RockModelManager::initialize(std::vector<Geometry*> in_geometryVec)
{
	this->createModels(in_geometryVec);
}
