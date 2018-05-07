#pragma once
#ifndef CUBEMANAGER_H
#define CUBEMANAGER_H
#include"..\Objects\CubeModel.h"
#include"..\Shaders\BasicShader.h"
#include"..\Shaders\NormalMapShader.h"
#include"..\Player\Player.h"
#include"..\Managers\InputHandler.h"
#include"..\Player\Interaction.h"
#include"..\Objects\PedestalModel.h"
#include<map>

class CubeManager
{
private:
	ID3D11DeviceContext * context;
	ID3D11Device * device;
	std::vector<CubeModel*> m_cubes;
	std::vector<PedestalModel*> m_pedestals;
	int lastPickedCubeID = -1;

	Camera * pCam;
	Player * pPlayer;
	Interaction * pInteraction;

	BasicShader * m_BasicShader;
	NormalMapShader * m_NormalMapShader;
	

	void updateCube(const int &n);
	int checkCollision();
	bool checkBoxPedestal();
public:
	CubeManager();
	~CubeManager();
	bool initialize(std::vector<std::vector<Mesh*>> const &cubes, std::vector<Mesh*> const &pedestals, 
					ID3D11DeviceContext * pDevCon, ID3D11Device* pDev, Camera* pCam, Interaction* pInteraction);

	void update();
	void Draw(DirectX::XMMATRIX in_Proj, DirectX::XMMATRIX in_View);


};
#endif // !CUBEMANAGER_H
