#ifndef STATICMODELMANAGER_H
#define STATICMODELMANAGER_H
#include"..\Importer\Geometry.h"
#include"..\Managers\WallModelManager.h"
#include"..\Managers\InputHandler.h"
#include"..\Managers\TreeManager.h"

#include"d3d11.h"
#include<vector>
 
class StaticModelManager
{
private:

	WallModelManager wallManager;
	TreeManager treeManager;
	//to add more managers

public:
	StaticModelManager();
	~StaticModelManager();

	void update(const Dimension &in_dim);
	void Draw();
	void initialize(std::vector<Geometry*> in_geometry, Camera* in_camera, ID3D11Device* in_device, ID3D11DeviceContext * in_context);

};

#endif // !STATICMODELMANAGER_H
