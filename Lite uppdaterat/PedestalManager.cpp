#include "stdafx.h"
#include "PedestalManager.h"

PedestalManager::PedestalManager()
{

}

PedestalManager::~PedestalManager()
{
	delete this->m_NormalMapShader;
	delete this->m_BasicShader;
}

bool PedestalManager::initialize(std::vector<std::vector<Mesh*>> const &pedestalModels, ID3D11DeviceContext * pDevCon, ID3D11Device* pDev)
{
	this->pDevCon = pDevCon;
	this->pDev = pDev;

	m_BasicShader = new BasicShader();
	//m_NormalMapShader = new NormalMapShader();

	m_BasicShader->init(pDev, pDevCon);
	m_BasicShader->createShader(SHADERTYPE::VertexPosNormCol);
	//m_NormalMapShader->init(pDev, pDevCon);
	//m_NormalMapShader->createShader(NORMALMAP_SHADER_TYPE::NO_COLOR);

	Matrix world = Matrix::CreateRotationZ(DirectX::XM_PI);
	PedestalModel * pPedestalOne = new PedestalModel(world, true, true, true, 1, Color(1, 0, 0));	

	pPedestalOne->setMeshes(pedestalModels[0]);

	/*pWallOne->setBasicShader(m_Shader);
	pWallTwo->setBasicShader(m_Shader);*/

	pPedestalOne->setBasicShader(m_BasicShader);	

	m_models.push_back(pPedestalOne);

	return true;
}


void PedestalManager::Update()
{
	for (size_t i = 0; i < m_models.size(); i++)
	{
		m_models[i]->Update();
	}
}

void PedestalManager::Draw(DirectX::XMMATRIX in_View, DirectX::XMMATRIX in_Proj)
{

	m_BasicShader->setBlendState(); //default
	m_BasicShader->setDepthStencilState(); //default
	m_BasicShader->setRasterizerState(); //default
	m_BasicShader->setSamplerState(); //default

	pDevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	for (size_t i = 0; i < m_models.size(); i++)
	{
		m_models[i]->Draw(pDevCon, in_View, in_Proj);
	}
}