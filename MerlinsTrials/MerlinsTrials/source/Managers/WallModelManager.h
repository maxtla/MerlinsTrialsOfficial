#ifndef WALLMODELMANAGER_H
#define WALLMODELMANAGER_H
#include<vector>
#include"..\Importer\Geometry.h"
#include"..\Objects\WallModel.h"
#include"..\Managers\ModelManagerBase.h"
#define WALLO "WallO"
#define WALL "Wall"

class WallModelManager : public ModelManagerBase
{
private:
	std::vector<WallModel> walls; //all other walls, can turn invisible
	std::vector<WallModel> oWalls; //surrounding walls
	//add more wall types - Brick, wooden etc.

	void createShaders();
	void createModels(std::vector<Geometry*> in_geometryVec);
public:
	WallModelManager();
	WallModelManager(Camera* in_camera, ID3D11Device* in_device, ID3D11DeviceContext * in_context);
	~WallModelManager();

	
	void update(const Dimension &in_dim);
	void Draw();
	void initialize(std::vector<Geometry*> in_geometryVec);

};
#endif // !WALLMODELMANAGER_H
