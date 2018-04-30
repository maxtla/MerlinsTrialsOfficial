#ifndef LEVELONE_H
#define LEVELONE_H
#include<string>
#include"..\Helpers\Enumerators.h"
#include"..\Managers\DynamicModelManager.h"
#include"..\Managers\StaticModelManager.h"
#include"..\Managers\GeometryManager.h"
#include"..\Player\Player.h"
#include"..\Collision\Collision.h"
#include"..\Shaders\Shaders.h"


class TerrainModel;
class WallModel;

#define LEVEL_ONE_PATH "TestTri.obj"

class LevelOne
{	
private:
	ID3D11Device* device;
	ID3D11DeviceContext * deviceContext;
	GeometryManager geometryManager;
	DynamicModelManager dynamicManager;
	StaticModelManager staticManager;

	std::vector<Geometry*> geometryVec;
	Collision collideManager;

	void importLevel();
	void collisionCheck();
public:
	LevelOne();
	~LevelOne();

	void Draw();
	void update(const Dimension &in_dim);
	void initialize(ID3D11Device * in_device, ID3D11DeviceContext* in_deviceContext, Player* in_player);
	


};

#endif // !LEVELONE_H
