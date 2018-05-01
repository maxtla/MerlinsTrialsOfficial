#pragma once
#ifndef _WALL_MANAGER_H
#define _WALL_MANAGER_H
#include "..\Objects\WallModel.h"
#include "..\Shaders\BasicShader.h"
#include "..\Shaders\NormalMapShader.h"

class WallManager
{
public:
	WallManager();
	~WallManager();
	bool initialize(std::vector<std::vector<Mesh*>> const &wallModels, ID3D11DeviceContext * pDevCon, ID3D11Device* pDev);

	void Update();
	void Draw(DirectX::XMMATRIX in_Proj, DirectX::XMMATRIX in_View);

private:
	ID3D11DeviceContext * pDevCon;
	ID3D11Device * pDev;
	std::vector<WallModel*> m_BasicWalls;
	BasicShader * m_BasicShader;
	NormalMapShader * m_NormalMapShader;
};
#endif // !_WALL_MANAGER_H

