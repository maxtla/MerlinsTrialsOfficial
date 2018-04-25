#ifndef LEVELONE_H
#define LEVELONE_H
#include<string>
#include"..\Helpers\Enumerators.h"
#include"..\Managers\WallModelManager.h"
#include"..\Managers\StaticModelManager.h"
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
	
	WallModelManager wallManager;
	StaticModelManager staticManager;

	Collision collideManager;
	
public:
	LevelOne();
	~LevelOne();

	void DrawLevel();

	void collisionCheck();
	bool initialize(ID3D11Device * in_device, ID3D11DeviceContext* in_deviceContext, const std::string &in_fileName, Player* player);
	
	void initializeWallManager(std::vector<Geometry*> in_var);
	void initializeStaticManager(std::vector<Geometry*> in_var);

};

#endif // !LEVELONE_H
