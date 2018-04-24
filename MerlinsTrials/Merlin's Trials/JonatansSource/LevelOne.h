#ifndef LEVELONE_H
#define LEVELONE_H
#include"ObjectImporter.h"
#include"Geometry.h"
#include<string>
#include"Enumerators.h"
#include"WallManager.h"
#include"TerrainManager.h"
#include"WaterManager.h"
#include"MiscManager.h"
#include"Player.h"
#include"Collision.h"
#include"Shaders.h"

class LevelOne
{	
public:
	std::vector<Geometry> geometryVec;
	std::vector<TerrainModel> terrainModels;
	std::vector<WallModel> wallModels;
	std::vector<WallModel> boundryWalls;
	std::vector<ModelBase> miscModels;

private:

	struct Matrices
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};
	Matrices matrices;

	ObjectImporter* objImporter;
	std::string fileName;
	ID3D11Device* device;
	ID3D11DeviceContext * deviceContext;
	ID3D11Buffer * constBuffer;

	WallManager normalWallManager;
	WallManager otherWallManager;
	TerrainManager terrainManager;
	WaterManager waterManager;
	MiscManager miscManager;

	Collision collideManager;
	Player* player;
	Dimension cDimension;


	void createCB();
	void createModel(const std::string &meshName, const int &i);
	void updateMatrices(const DirectX::XMMATRIX &in_matrix);
	void rebindCB();
public:
	LevelOne();
	~LevelOne();

	void Draw();
	void collisionCheck();
	bool initialize(ID3D11Device * in_device, ID3D11DeviceContext* in_deviceContext, ObjectImporter * importer, const std::string &in_fileName, Player* player);
	bool initializeModels();
	void setDimension(const Dimension &in_dimension);
	Dimension getCurrentDimension() const;
};

#endif // !LEVELONE_H
