#ifndef LEVELONE_H
#define LEVELONE_H
#include"ObjectImporter.h"
#include"Geometry.h"
#include<string>
#include"Enumerators.h"
#include"WallModel.h"
#include"TerrainModel.h"
#include"Player.h"
#include"Collision.h"

class LevelOne
{	
public:
	std::vector<Geometry> geometryVec;
	std::vector<TerrainModel> terrainModels;
	std::vector<WallModel> wallModels;
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



	Collision collideManager;
	Player* player;
	
	void createCB();
	void createModel(const std::string &meshName, const int &i);
	void updateMatrices(const DirectX::XMMATRIX &in_matrix);
	void rebindCB();
public:
	LevelOne();
	~LevelOne();

	void Draw();
	void collisionCheck();
	bool initialize(ID3D11Device * in_device, ObjectImporter * importer, const std::string &in_fileName, Player* player);
	bool initializeModels();
};

#endif // !LEVELONE_H
