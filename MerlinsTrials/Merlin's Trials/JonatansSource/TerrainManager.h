#ifndef TERRAINMANAGER_H
#define TERRAINMANAGER_H
#include<vector>
#include"TerrainModel.h"

class TerrainModel;
class TerrainManager
{
private:
	std::vector<TerrainModel> models;

public:
	TerrainManager();
	~TerrainManager();
};
#endif // !TERRAINMODEL_H
