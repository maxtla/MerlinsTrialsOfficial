#ifndef LEVELONE_H
#define LEVELONE_H
#include<string>
#include"Enumerators.h"
#include"WallModelManager.h"
#include"StaticModelManager.h"
#include"Player.h"
#include"Collision.h"
#include"Shaders.h"


class TerrainModel;
class WallModel;

class LevelOne
{	
public:


private:

	struct Matrices
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};
	Matrices matrices;

	std::string fileName;
	ID3D11Device* device;
	ID3D11DeviceContext * deviceContext;
	ID3D11Buffer * constBuffer;
	
	WallModelManager wallManager;
	StaticModelManager staticManager;


	Collision collideManager;
	Player* player;
	
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
