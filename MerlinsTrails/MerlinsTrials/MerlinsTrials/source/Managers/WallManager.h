#pragma once
#ifndef _WALL_MANAGER_H
#define _WALL_MANAGER_H
#include "..\Objects\WallModel.h"
#include "..\Shaders\BasicShader.h"
#include "..\Player\Player.h"
#include <d3d11.h>

class WallManager
{
public:
	WallManager();
	~WallManager();
	bool initialize(std::vector<Mesh*>  &levelMeshes, ID3D11DeviceContext * pDevCon, ID3D11Device* pDev);

	void Update();
	void Draw(DirectX::XMMATRIX in_View, DirectX::XMMATRIX in_Proj);
	void setPlayer(Player* player) { this->pPlayer = player; }
private:
	Player * pPlayer;
	ID3D11DeviceContext * pDevCon;
	ID3D11Device * pDev;
	std::vector<WallModel*> m_BasicWalls;
	BasicShader * m_BasicShader;

	void checkPlayerCollision();
};
#endif // !_WALL_MANAGER_H

