#include "stdafx.h"
#include "DynamicModelManager.h"

DynamicModelManager::DynamicModelManager()
{
}

DynamicModelManager::DynamicModelManager(InputHandler * in_input)
{
	this->input_handler = in_input;
}

DynamicModelManager::~DynamicModelManager()
{
}

void DynamicModelManager::initialize(std::vector<Geometry*> in_geometry, Camera* in_camera, ID3D11Device* in_device, ID3D11DeviceContext* in_context)
{


}

void DynamicModelManager::Draw()
{
}
