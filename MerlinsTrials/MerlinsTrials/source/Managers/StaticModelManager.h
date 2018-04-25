#ifndef STATICMODELMANAGER_H
#define STATICMODELMANAGER_H
#include"..\Importer\Geometry.h"
#include"..\Objects\TerrainModel.h"
#include"..\Objects\LeavesModel.h"
#include"..\Objects\TrunkModel.h"
#include"..\Managers\ManagerBase.h"

#include"d3d11.h"
#include<vector>

class StaticModelManager : public ManagerBase
{
private:
	std::vector<Geometry*> geometry;
	std::vector<TerrainModel> terrianModels;
	std::vector<TrunkModel> trunkModels;
	std::vector<LeavesModel> leavesModels;

	void rebindCB();
	void createModels();
public:
	StaticModelManager();
	StaticModelManager(Player* in_player, ID3D11Device* in_device, ID3D11DeviceContext * in_context);
	~StaticModelManager();

	void DrawModels();
	void initialize(std::vector<Geometry*> in_var);

};

#endif // !STATICMODELMANAGER_H
