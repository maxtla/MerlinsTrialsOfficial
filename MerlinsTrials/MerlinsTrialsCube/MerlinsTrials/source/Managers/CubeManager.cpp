#include "stdafx.h"
#include "CubeManager.h"

CubeManager::CubeManager()
{
}

CubeManager::~CubeManager()
{
}

bool CubeManager::initialize(std::vector<std::vector<Mesh*>> const &meshes, ID3D11DeviceContext * pDevCon, ID3D11Device * pDev)
{
	this->context = pDevCon;
	this->device = pDev;

	m_BasicShader = new BasicShader();
	m_NormalMapShader = new NormalMapShader();

	m_BasicShader->init(pDev, pDevCon);
	m_BasicShader->createShader(SHADERTYPE::VertexPosNormTex);
	m_NormalMapShader->init(pDev, pDevCon);
	m_NormalMapShader->createShader(NORMALMAP_SHADER_TYPE::NO_COLOR);

	CubeModel * cModel = new CubeModel(DirectX::XMMatrixTranslation(1.0f, 1.0f, 1.0f), true, true, 7);

	cModel->setMeshes(meshes[0]);
	cModel->setNormalMapShader(this->m_NormalMapShader);

	this->m_cubes.push_back(cModel);

	return true;
}

void CubeManager::update()
{
	//if E is pressed
	if (1)
	{
		this->checkCollision();
	}

	for (auto var : this->m_cubes)
	{
		var->update();
	}
	

}

void CubeManager::Draw(DirectX::XMMATRIX in_Proj, DirectX::XMMATRIX in_View)
{
	this->m_NormalMapShader->setBlendState();
	this->m_NormalMapShader->setDepthStencilState();
	this->m_NormalMapShader->setRasterizerState();
	this->m_NormalMapShader->setSamplerState();
	
	this->context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	for (auto var : this->m_cubes)
	{
		var->Draw(this->context, in_View, in_Proj);
	}
}

int CubeManager::checkCollision()
{
	bool hit = false;
	float distance = INFINITY;
	for (auto var : this->m_cubes)
	{
		XMVECTOR tempForward = this->cam->getCamForward();
		XMVECTOR tempCam = this->cam->getCamPos();
		if (var->getBoundingBox().Intersects(tempCam, tempForward, distance))
		{
			//Intersects
			if (distance <= var->getGrabDistance())
			{
				//within range
				hit = true;

			}
		}
	}
	return ;
}
