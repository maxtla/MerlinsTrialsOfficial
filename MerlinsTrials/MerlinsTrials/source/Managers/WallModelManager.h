#ifndef WALLMODELMANAGER_H
#define WALLMODELMANAGER_H
#include<vector>
#include"..\Importer\Geometry.h"
#include"..\Objects\WallModel.h"
#include"..\Shaders\Shaders.h"
#include"..\Player\Camera.h"
#include"..\Helpers\Enumerators.h"

#define WALLO "WallO"
#define WALL "Wall"

class WallModelManager
{
private:
	std::vector<WallModel> walls; //all other walls, can turn invisible
	std::vector<WallModel> oWalls; //surrounding walls
	//add more wall types - Brick, wooden etc.

	Camera* camera;
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	Dimension current_dim;

	void createModels(std::vector<Geometry*> in_geometryVec);
public:
	WallModelManager();
	WallModelManager(Camera* in_camera, ID3D11Device* in_device, ID3D11DeviceContext * in_context);
	~WallModelManager();

	
	void update(const Dimension &in_dim);
	void Draw();
	void initialize(std::vector<Geometry*> in_geometry);

};
#endif // !WALLMODELMANAGER_H
