#pragma once
#ifndef STATICMODELMANAGER_H
#define STATICMODELMANAGER_H
#include "..\Managers\TerrainManager.h"
#include <vector>
#include "..\Managers\WallModelManager.h"

class StaticModelManager
{
private:

	TerrainManager* terrainManager;
	WallModelManager* wallManager;
	TrunkManager* trunkManager;
	LeavesManager* leavesManager;	

public:
	StaticModelManager();
	~StaticModelManager();

	void Draw();
	void initialize(std::vector<Mesh*> in_var, ID3D11DeviceContext* pDevCon, ID3D11Device* device);

};

#endif // !STATICMODELMANAGER_H
