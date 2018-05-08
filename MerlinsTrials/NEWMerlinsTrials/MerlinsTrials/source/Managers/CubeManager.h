#pragma once
#ifndef CUBEMANAGER_H
#define CUBEMANAGER_H
#include"..\Shaders\BasicShader.h"
#include"..\Shaders\NormalMapShader.h"
#include"..\Player\Player.h"
#include"..\Objects\PedestalModel.h"
#include"..\Objects\CubeModel.h"

class CubeManager
{
private:
	ID3D11DeviceContext * context;
	ID3D11Device * device;
	BasicShader * m_BasicShader;
	NormalMapShader * m_NormalMapShader;

	std::vector<CubeModel*> m_ForestCubes;
	std::vector<CubeModel*> m_LabyrinthCubes;
	std::vector<PedestalModel*> m_ForestPedestals;
	std::vector<PedestalModel*> m_LabyrinthPedestals;

	Player * pPlayer;
	ObjectImporter importer;

	
	int checkCollision();
	bool checkBoxPedestal();
	bool checkPickUp();
public:
	CubeManager();
	~CubeManager();
	bool initialize(ID3D11DeviceContext * pDevCon, ID3D11Device* pDev, Player* in_player);

	void update();
	void Draw(DirectX::XMMATRIX in_Proj, DirectX::XMMATRIX in_View);


};
#endif // !CUBEMANAGER_H
