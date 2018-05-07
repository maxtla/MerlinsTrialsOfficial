#include "stdafx.h"
#include "WallManager.h"


WallManager::WallManager()
{
}


WallManager::~WallManager()
{
}

bool WallManager::initialize(std::vector<Mesh*> &levelMeshes, ID3D11DeviceContext * pDevConP, ID3D11Device * pDevP)
{
	this->pDevCon = pDevConP;
	this->pDev = pDevP;

	m_BasicShader = new BasicShader();

	m_BasicShader->init(pDev, pDevCon);
	m_BasicShader->createShader(SHADERTYPE::VertexPosNormCol);

	WallModel * pWall = nullptr;
	std::vector<Mesh*> walls;
	for (auto var : levelMeshes)
	{
		if (var->getName() == "Wall" || var->getName() == "WallO" ||)
		{
			pWall = new WallModel(DirectX::XMMatrixIdentity());
			walls.push_back(var);
			pWall->setMeshes(walls);
			pWall->setBasicShader(m_BasicShader);
			walls.clear();

			m_BasicWalls.push_back(pWall);
			pWall = nullptr;
		}
	}


	return true;
}

void WallManager::Update()
{
	for (size_t i = 0; i < m_BasicWalls.size(); i++)
	{
		m_BasicWalls[i]->Update();
	}
	checkPlayerCollision();
}

void WallManager::Draw(DirectX::XMMATRIX in_View, DirectX::XMMATRIX in_Proj)
{
	//clear pre-existing states before setting new ones (also means we need to move ViewPorts to shader class)
	//m_Shader->gDeviceContext->ClearState();
	//each manager sets up its own shader and states for the current G-pipeline
	m_BasicShader->setBlendState(); //default
	m_BasicShader->setDepthStencilState(); //default
	m_BasicShader->setRasterizerState(); //default
	m_BasicShader->setSamplerState(); //default


	pDevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	for (size_t i = 0; i < m_BasicWalls.size(); i++)
	{
		m_BasicWalls[i]->Draw(pDevCon, in_View, in_Proj);
	}
}

void WallManager::checkPlayerCollision()
{
	std::vector<BoundingOrientedBox> collisions;
	for (auto var : this->m_BasicWalls)
	{
		for (auto mesh : var->getMeshes())
		{
			BoundingOrientedBox test;
			if (mesh->hasAABB)
			{
				test.CreateFromBoundingBox(test, mesh->m_AABB);
			}
			else if (mesh->hasOBB)
			{
				test = mesh->m_OBB;
			}
			if (test.Intersects(*this->pPlayer->getAvatar()))
			{
				//Intersects
				collisions.push_back(test);
			}
		}

	}
	if (!collisions.empty())
	{
		this->pPlayer->handleWallCollision(collisions);
	}
	collisions.clear();
}