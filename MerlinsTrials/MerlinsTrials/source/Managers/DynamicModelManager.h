#ifndef DYNAMICMODELMANAGER_H
#define DYNAMICMODELMANAGER_H
#include"..\Managers\InputHandler.h"
#include"..\Player\Player.h"
#include"..\Importer\Geometry.h"
#include"..\Helpers\Enumerators.h"
#include<vector>

class DynamicModelManager
{
private:

	//add dynamicObjects vectors

public:
	DynamicModelManager();
	~DynamicModelManager();

	void update(const Dimension &in_dim);
	void Draw();
	void initialize(std::vector<Geometry*> in_geometry, Player* in_player, ID3D11Device* in_device, ID3D11DeviceContext* in_context);


};
#endif // !DYNAMICMODELMANAGER_H
