#ifndef DYNAMICMODELMANAGER_H
#define DYNAMICMODELMANAGER_H
#include"..\Managers\InputHandler.h"
#include"..\Player\Camera.h"
#include"..\Importer\Geometry.h"
#include<vector>

class DynamicModelManager
{
private:
	InputHandler* input_handler;

	//add dynamicObjects vectors

	void createModels();
public:
	DynamicModelManager();
	DynamicModelManager(InputHandler* in_input;
	~DynamicModelManager();

	void update();
	void Draw();
	void initialize(std::vector<Geometry*> in_geometry, Camera* in_camera, ID3D11Device* in_device, ID3D11DeviceContext* in_context);


};
#endif // !DYNAMICMODELMANAGER_H
