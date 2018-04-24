#ifndef TERRAINMANAGER_H
#define TERRAINMANAGER_H
#include<vector>
#include"TerrainModel.h"


class TerrainManager
{
private:
	std::vector<TerrainModel>* models;

public:
	TerrainManager();
	~TerrainManager();

	void initialize(ID3D11Device * in_device, ID3D11DeviceContext * in_deviceContext);
	void setModelPtr(std::vector<TerrainModel>* in_models);
};
#endif // !TERRAINMODEL_H
