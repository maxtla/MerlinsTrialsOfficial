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

class LevelOne
{	
public:


private:
	ID3D11Device* device;
	ID3D11DeviceContext * deviceContext;
	Timer timer;
	Dimension current_dim;
	InputHandler* input_handler;

	GeometryManager geoManager;
	DynamicModelManager dynamicManager;
	StaticModelManager staticManager;

	Collision collideManager;
	void checkDim();
public:
	LevelOne();
	~LevelOne();

	void DrawLevel();
	void update();
	void collisionCheck();
	bool initialize(std::vector<Geometry*> in_geometryVec, ID3D11Device * in_device, ID3D11DeviceContext* in_deviceContext, Player* in_player, InputHandler* in_handler);
	


};

#endif // !LEVELONE_H
