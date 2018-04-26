#include "stdafx.h"
#include "TreeManager.h"

TreeManager::TreeManager()
{
}

TreeManager::TreeManager(Camera * in_camera, ID3D11Device * in_device, ID3D11DeviceContext * in_context)
{
	this->camera = in_camera;
	this->device = in_device;
	this->context = in_context;
}

TreeManager::~TreeManager()
{
}

void TreeManager::update(const Dimension & in_dim)
{
	this->current_dim = in_dim;
}

void TreeManager::Draw()
{
	switch (this->current_dim)
	{
	case Dimension::NORMAL:
		break;
	case Dimension::OTHER:
		break;
	}
}

void TreeManager::initialize(std::vector<Geometry*> in_geometry)
{
	this->createModels(in_geometry);
}

void TreeManager::createModels(std::vector<Geometry*> in_geometry)
{
	for (auto var : in_geometry)
	{
		std::string name = var->getName();

		auto pos = name.find("_");
		if (pos == std::string::npos)
		{
			exit(-1);
		}

		name = name.substr(0, pos - 1);
		if (var->getName() == TreeTrunk)
		{
			this->trunks.push_back(TrunkModel(var, this->context));
		}
		if (var->getName() == TreeLeaves)
		{
			this->leaves.push_back(LeavesModel(var, this->context));
		}
	}
}
