#include "stdafx.h"
#include "WallManager.h"


WallManager::WallManager()
{
}


WallManager::~WallManager()
{
}

bool WallManager::initialize(std::vector<std::vector<Mesh*>> const &wallModels, ID3D11DeviceContext * pDevCon, ID3D11Device * pDev)
{
	this->pDevCon = pDevCon;
	this->pDev = pDev;

	m_BasicShader = new BasicShader();
	m_NormalMapShader = new NormalMapShader();

	m_BasicShader->init(pDev, pDevCon);
	m_BasicShader->createShader(SHADERTYPE::VertexPosNormTex);
	m_NormalMapShader->init(pDev, pDevCon);
	m_NormalMapShader->createShader(NORMALMAP_SHADER_TYPE::NO_COLOR);

	WallModel * pWallOne = new WallModel(DirectX::XMMatrixIdentity());
	WallModel * pWallTwo = new WallModel(DirectX::XMMatrixTranslation(1.0f, 0.5f, 3.0f));

	pWallOne->setMeshes(wallModels[0]);
	pWallTwo->setMeshes(wallModels[0]);

	/*pWallOne->setBasicShader(m_Shader);
	pWallTwo->setBasicShader(m_Shader);*/

	pWallOne->setNormalMapShader(m_NormalMapShader);
	pWallTwo->setNormalMapShader(m_NormalMapShader);

	m_BasicWalls.push_back(pWallOne);
	m_BasicWalls.push_back(pWallTwo);


	return true;
}

void WallManager::Update()
{
	for (size_t i = 0; i < m_BasicWalls.size(); i++)
	{
		m_BasicWalls[i]->Update();
	}
}

void WallManager::Draw(DirectX::XMMATRIX in_Proj, DirectX::XMMATRIX in_View)
{
	//clear pre-existing states before setting new ones (also means we need to move ViewPorts to shader class)
	//m_Shader->gDeviceContext->ClearState();
	//each manager sets up its own shader and states for the current G-pipeline
	//m_Shader->setBlendState(); //default
	//m_Shader->setDepthStencilState(); //default
	//m_Shader->setRasterizerState(); //default
	//m_Shader->setSamplerState(); //default

	m_NormalMapShader->setBlendState(); //default
	m_NormalMapShader->setDepthStencilState(); //default
	m_NormalMapShader->setRasterizerState(); //default
	m_NormalMapShader->setSamplerState(); //default

	pDevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	for (size_t i = 0; i < m_BasicWalls.size(); i++)
	{
		m_BasicWalls[i]->Draw(pDevCon, in_View, in_Proj);
	}
}
