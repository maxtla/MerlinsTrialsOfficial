#include "WallManager.h"

WallManager::WallManager()
{
	this->models = nullptr;
	this->device = nullptr;
	this->deviceContext = nullptr;
}

WallManager::~WallManager()
{
}

void WallManager::initialize(ID3D11Device * in_device, ID3D11DeviceContext * in_deviceContext)
{
	this->device = in_device;
	this->deviceContext = in_deviceContext;

	/*
	INIT SHADER
	*/

}

void WallManager::setModelPtr(std::vector<WallModel>* in_models, std::vector<WallModel>* in_otherModels)
{
	this->models = in_models;
	this->otherModels = in_otherModels;
}
