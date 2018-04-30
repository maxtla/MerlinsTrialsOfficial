#pragma once
#ifndef ROCKMODELMANAGER_H
#define ROCKMODELMANAGER_H
#include<vector>
#include"..\Objects\RockModel.h"
#include"..\Managers\ModelManagerBase.h"

class RockModelManager : public ModelManagerBase
{
private:
	std::vector<RockModel> oRocks; //boundry rocks;
	std::vector<RockModel> sRocks; //rocks laying around

	void createShaders();
	void createModels(std::vector<Geometry*> in_geometryVec);
public:
	RockModelManager();
	RockModelManager(Camera* in_camera, ID3D11Device* in_device, ID3D11DeviceContext* in_context);
	~RockModelManager();

	void update(const Dimension &in_dim);
	void Draw();
	void initialize(std::vector<Geometry*> in_geometryVec);
};
#endif // !ROCKMODELMANAGER_H
