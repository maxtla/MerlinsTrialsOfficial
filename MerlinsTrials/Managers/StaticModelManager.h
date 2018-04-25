#ifndef STATICMODELMANAGER_H
#define STATICMODELMANAGER_H
#include"Geometry.h"
#include"TerrainModel.h"
#include"Shaders.h"
#include<vector>

class StaticModelManager
{
private:
	std::vector<Geometry>* geometry;
	std::vector<TerrainModel> terrianModels;
	std::vector<TrunkModel> trunkModels;
	std::vector<LeavesModel> leavesModels;

	Shaders shaderComponent;

	void createModels();
public:
	StaticModelManager();
	~StaticModelManager();

	void DrawModels();
	void initialize(std::vector<Geometry*> in_var);

};

#endif // !STATICMODELMANAGER_H
