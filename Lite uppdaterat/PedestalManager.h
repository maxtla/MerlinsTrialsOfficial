#pragma once
#ifndef PEDESTALMANAGER_H
#define PEDESTALMANAGER_H
#include "..\Objects\PedestalModel.h"
class PedestalManager
{
private:
	std::vector<PedestalModel*> m_models;

	ID3D11DeviceContext * pDevCon;
	ID3D11Device * pDev;
	
	BasicShader * m_BasicShader;
	NormalMapShader * m_NormalMapShader;

public:
	PedestalManager();
	~PedestalManager();

	bool initialize(std::vector<std::vector<Mesh*>> const &pedestalModels, ID3D11DeviceContext * pDevCon, ID3D11Device* pDev);

	void Update();
	void Draw(DirectX::XMMATRIX in_View, DirectX::XMMATRIX in_Proj);

};


#endif
