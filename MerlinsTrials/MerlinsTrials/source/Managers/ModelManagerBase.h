#pragma once
#ifndef MODELMANAGERBASE_H
#define MODELMANAGERBASE_H
#include<vector>
#include"..\Importer\Geometry.h"
#include"..\Shaders\Shaders.h"
#include"..\Player\Camera.h"
#include"..\Helpers\Enumerators.h"

class ModelManagerBase
{
protected:
	ID3D11Device * device;
	ID3D11DeviceContext * context;
	Camera* camera;
	Dimension current_dim;

	//one per shader or technique?
	std::vector<Shaders> shaders;

	virtual void createShaders() = 0;
	virtual void createModels(std::vector<Geometry*> in_geometryVec) = 0;
public:
	ModelManagerBase();
	ModelManagerBase(Camera* in_camera, ID3D11Device* in_device, ID3D11DeviceContext * in_context);
	~ModelManagerBase();

	virtual void update(const Dimension &in_dim) = 0;
	virtual void Draw() = 0;
	virtual void initialize(std::vector<Geometry*> in_geometryVec) = 0;
};
#endif // !MODELMANAGERBASE_H
