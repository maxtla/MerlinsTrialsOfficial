#ifndef WALLMODELMANAGER_H
#define WALLMODELMANAGER_H
#include<vector>
#include"..\Importer\Geometry.h"
#include"..\Objects\WallModel.h"
#include"..\Shaders\Shaders.h"
#include"..\Managers\ManagerBase.h"


#define WALLO "WallO"
#define WALL "Wall"

class WallModelManager : public ManagerBase
{
private:
	std::vector<Geometry*> geometry;
	std::vector<WallModel> walls; //all other walls
	std::vector<WallModel> oWalls; //surrounding walls

	void rebindCB();
	void createModels();
public:
	WallModelManager();
	WallModelManager(Player* in_player, ID3D11Device* in_device, ID3D11DeviceContext * in_context);
	~WallModelManager();

	void DrawModels();
	void initialize(std::vector<Geometry*> in_var);

};
#endif // !WALLMODELMANAGER_H
