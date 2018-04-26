#ifndef STATICMODELMANAGER_H
#define STATICMODELMANAGER_H
#include"..\Importer\Geometry.h"
#include"..\Managers\WallModelManager.h"
#include"..\Managers\InputHandler.h"

#include"d3d11.h"
#include<vector>
 
class StaticModelManager
{
private:
	Timer timer;
	Dimension current_dim;
	InputHandler* input_handler;
	WallModelManager wallManager;

	//to add more managers
	bool checkDim();
public:
	StaticModelManager();
	StaticModelManager(InputHandler* in_handler);
	~StaticModelManager();

	void update();
	void Draw();
	void initialize(std::vector<Geometry*> in_geometry, Camera* in_camera, ID3D11Device* in_device, ID3D11DeviceContext * in_context);

};

#endif // !STATICMODELMANAGER_H
