#include "StaticModelManager.h"



StaticModelManager::StaticModelManager()
{
}

StaticModelManager::~StaticModelManager()
{
}

void StaticModelManager::update(const Dimension &in_dim)
{
	this->wallManager.update(in_dim);
	this->treeManager.update(in_dim);
	this->rockManager.update(in_dim);
}

void StaticModelManager::Draw()
{

	this->wallManager.Draw();
	this->treeManager.Draw();
	this->rockManager.Draw();
	//draw other managers

}

void StaticModelManager::initialize(std::vector<Geometry*> in_geometry, Camera* in_camera, ID3D11Device* in_device, ID3D11DeviceContext * in_context)
{	
	//initiate managers
	this->wallManager = WallModelManager(in_camera, in_device, in_context);
	this->wallManager.initialize(in_geometry);

	this->treeManager = TreeManager(in_camera, in_device, in_context);
	this->treeManager.initialize(in_geometry);

	this->rockManager = RockModelManager(in_camera, in_device, in_context);
	this->rockManager.initialize(in_geometry);


	//add other managers
	//here
}
