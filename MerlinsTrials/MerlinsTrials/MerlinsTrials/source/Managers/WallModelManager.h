#ifndef WALLMODELMANAGER_H
#define WALLMODELMANAGER_H
#include<vector>
#include"Geometry.h"
#include"WallModel.h"
#include"Shaders.h"

#define WALLO "WallO"
#define WALL "Wall"

class WallModelManager
{
private:
	std::vector<Geometry*> geometry;
	std::vector<WallModel> walls; //all other walls
	std::vector<WallModel> oWalls; //surrounding walls

	Shaders shaderComponent;

	void createModels();
public:
	WallModelManager();
	~WallModelManager();

	void DrawModels();
	void initialize(std::vector<Geometry*> in_var);

};
#endif // !WALLMODELMANAGER_H
