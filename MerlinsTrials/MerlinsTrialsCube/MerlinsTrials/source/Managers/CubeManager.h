#pragma once
#ifndef CUBEMANAGER_H
#define CUBEMANAGER_H
#include"..\Objects\CubeModel.h"
#include"..\Shaders\BasicShader.h"
#include"..\Shaders\NormalMapShader.h"
#include"..\Player\Player.h"

class CubeManager
{
private:
	ID3D11DeviceContext * context;
	ID3D11Device * device;
	std::vector<CubeModel*> m_cubes;
	Camera* cam;
	Player* player;

	BasicShader * m_BasicShader;
	NormalMapShader * m_NormalMapShader;
	bool isMoveable = true ;
	
	bool checkCollision();
public:
	CubeManager();
	~CubeManager();
	bool initialize(std::vector<std::vector<Mesh*>> const &wallModels, ID3D11DeviceContext * pDevCon, ID3D11Device* pDev);

	void update();
	void Draw(DirectX::XMMATRIX in_Proj, DirectX::XMMATRIX in_View);


};
#endif // !CUBEMANAGER_H
