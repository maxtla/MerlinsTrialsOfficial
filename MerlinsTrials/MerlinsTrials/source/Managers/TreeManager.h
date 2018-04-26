#ifndef TREEMANAGER_H
#define TREEMANAGER_H
#include"..\Objects\LeavesModel.h"
#include"..\Objects\TrunkModel.h"
#include"..\Objects\ModelBase.h"
#include"..\Player\Camera.h"
#include"..\Helpers\Enumerators.h"
#include<vector>

#define TreeTrunk "Trunk"
#define TreeLeaves "Leaves"

class TreeManager 
{
private:
	std::vector<LeavesModel> leaves;
	std::vector<TrunkModel> trunks;

	std::vector<Shaders> shaders;

	Camera* camera;
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	Dimension current_dim;

	void creataShaders();
	void createModels(std::vector<Geometry*> in_geometry);
public:
	TreeManager();
	TreeManager(Camera* in_camera, ID3D11Device* in_device, ID3D11DeviceContext* in_context);
	~TreeManager();

	void update(const Dimension &in_dim);
	void Draw();
	void initialize(std::vector<Geometry*> in_geometry);
};
#endif // !TREEMANAGER_H
