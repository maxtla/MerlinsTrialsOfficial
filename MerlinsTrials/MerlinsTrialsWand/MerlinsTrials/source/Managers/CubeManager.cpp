#include "stdafx.h"
#include "CubeManager.h"

CubeManager::CubeManager()
{
}

CubeManager::~CubeManager()
{
}

bool CubeManager::initialize(std::vector<std::vector<Mesh*>> const &meshes, ID3D11DeviceContext * pDevCon,
							ID3D11Device * pDev, Camera* pCam, Interaction* pInteraction)
{
	this->context = pDevCon;
	this->device = pDev;
	this->pCam = pCam;
	this->pInteraction = pInteraction;

	m_BasicShader = new BasicShader();
	m_NormalMapShader = new NormalMapShader();

	m_BasicShader->init(pDev, pDevCon);
	m_BasicShader->createShader(SHADERTYPE::VertexPosNormTex);
	m_NormalMapShader->init(pDev, pDevCon);
	m_NormalMapShader->createShader(NORMALMAP_SHADER_TYPE::NO_COLOR);
	int id = 0;
	id = this->generateUniqueID(id);
	CubeModel * cModel = new CubeModel(DirectX::XMMatrixTranslation(1.0f, -10.0f, 1.0f), true, true, id);

	cModel->setMeshes(meshes[0]);
	cModel->setNormalMapShader(this->m_NormalMapShader);

	this->m_cubes.push_back(cModel);
	this->cube_map.insert(std::pair<int, CubeModel*>(id, cModel));


	return true;
}

void CubeManager::update()
{
	//if E is pressed
	if (pInteraction->getEState())
	{
		switch (this->checkCollision())
		{
		case 1:
			this->updateCube(1);
			break;
		case 2:
			this->updateCube(2);
			break;
		case 3:
			this->updateCube(3);
			break;
		case 4:
			this->updateCube(4);
			break;
		case -1:
			pInteraction->setEState(false);
			break;
		}
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

void CubeManager::updateCube(const int & n)
{
	CubeModel * model = cube_map[n];
	Vector3 vec = pCam->getCamPos() + pCam->getCamForward();
	DirectX::XMMATRIX newW = XMMatrixMultiply(XMMatrixTranslation(vec.x, vec.y, vec.z), model->getWorld());
	model->setWorldMatrix(newW);
}

int CubeManager::generateUniqueID(int n)
{
	return n++;
}

int CubeManager::checkCollision()
{
	bool hit = false;
	float distance = INFINITY; //some standard value
	XMVECTOR forwardVec = this->pCam->getCamForward();
	XMVECTOR camPos = this->pCam->getCamPos();

	for (auto var : this->m_cubes)
	{
		if (var->getBoundingBox().Intersects(camPos, forwardVec, distance))
		{
			//Intersects
			if (distance <= var->getGrabDistance())
			{
				//within range
				return var->getID();
			}
		}
	}
	return -1;
}
