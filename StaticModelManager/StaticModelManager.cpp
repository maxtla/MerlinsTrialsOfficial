#include "StaticModelManager.h"

StaticModelManager::StaticModelManager()
{
}

StaticModelManager::~StaticModelManager()
{
	delete this->terrainManager;
	delete this->wallManager;
	delete this->trunkManager;
	delete this->leavesManager;
}

void StaticModelManager::Draw()
{		
	this->terrainManager->Draw();
	this->wallManager->Draw();
	this->trunkManager->Draw();
	this->leavesManager->Draw();
}

void StaticModelManager::initialize(MeshManager *in_var, ID3D11DeviceContext* pDevCon, ID3D11Device* device)
{
	std::vector<std::vector<Mesh*>> m_Walls = in_var->getM_Walls();
	std::vector<std::vector<Mesh*>> m_Terrain = in_var->getM_Terrain();
	std::vector<std::vector<Mesh*>> m_Trunk = in_var->getM_Trunk();
	std::vector<std::vector<Mesh*>> m_Leaves = in_var->getM_Leaves();

	this->terrainManager->initialize(m_Walls, pDevCon, device);
	this->wallManager->initialize(m_Terrain, pDevCon, device);
	this->trunkManager->initialize(m_Trunk, pDevCon, device);
	this->leavesManager->initialize(m_Leaves, pDevCon, device);
}
