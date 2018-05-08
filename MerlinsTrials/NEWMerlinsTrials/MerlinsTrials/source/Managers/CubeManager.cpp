#include "stdafx.h"
#include "CubeManager.h"

CubeManager::CubeManager()
{
}

CubeManager::~CubeManager()
{
}

bool CubeManager::initialize(ID3D11DeviceContext * pDevCon, ID3D11Device * pDev, Player* in_player)
{
	this->pPlayer = in_player;
	this->context = pDevCon;
	this->device = pDev;

	m_BasicShader = new BasicShader();
	m_NormalMapShader = new NormalMapShader();

	m_BasicShader->init(pDev, pDevCon);
	m_BasicShader->createShader(SHADERTYPE::VertexPosNormCol);
	m_NormalMapShader->init(pDev, pDevCon);
	m_NormalMapShader->createShader(NORMALMAP_SHADER_TYPE::WITH_COLOR);

	bool rValue = false;
	for (int i = 0; i < 4; i++)
	{
		this->m_ForestCubes.push_back(new CubeModel(XMMatrixIdentity() * XMMatrixScaling(0.1f,0.1f, 0.1f) * XMMatrixTranslation(2.f, 0.f, 0.f), true, true, i));
		this->m_LabyrinthCubes.push_back(new CubeModel(XMMatrixIdentity() * XMMatrixScaling(0.1f, 0.1f, 0.1f) * XMMatrixTranslation(-2.f, 0.f, 0.f), true, true, i));
		this->m_ForestPedestals.push_back(new PedestalModel(XMMatrixIdentity() * XMMatrixTranslation(0.f, 0.f, 2.f), true, true, i));
		this->m_LabyrinthPedestals.push_back(new PedestalModel(XMMatrixIdentity() * XMMatrixTranslation(0.f, 0.f, -2.f), true, true, i));
		
		this->m_ForestCubes[i]->setBasicShader(this->m_BasicShader);
		this->m_LabyrinthCubes[i]->setBasicShader(this->m_BasicShader);
		this->m_ForestPedestals[i]->setBasicShader(this->m_BasicShader);
		this->m_LabyrinthPedestals[i]->setBasicShader(this->m_BasicShader);
		
		switch (i)
		{
		case 0:
		{
			this->m_ForestCubes[i]->loadModel(CUBES_PATH0, this->device, this->context);
			this->m_ForestCubes[i]->setWorld(XMMatrixScaling(0.1f, 0.1f, 0.1f) * XMMatrixTranslation(1.f, 1.1f, 7.3f));
			this->m_LabyrinthCubes[i]->loadModel(CUBES_PATH0, this->device, this->context);
			this->m_LabyrinthCubes[i]->setWorld(XMMatrixScaling(0.1f, 0.1f, 0.1f) * XMMatrixTranslation(-8.4f, 0.3f, 0.15f));

			//röd
			this->m_ForestPedestals[i]->loadModel(PEDI_PATH0, this->device, this->context);
			this->m_ForestPedestals[i]->setWorld(XMMatrixRotationX(-XM_PI / 2) * XMMatrixTranslation(-8.8f, -.8f, 2.5f));
			this->m_LabyrinthPedestals[i]->loadModel(PEDI_PATH0, this->device, this->context);
			this->m_LabyrinthPedestals[i]->setWorld(XMMatrixRotationX(-XM_PI / 2) * XMMatrixTranslation(-18.7035f, -.8f, -2.6798f));
		}
			break;
		case 1:
		{
			this->m_ForestCubes[i]->loadModel(CUBES_PATH1, this->device, this->context);
			this->m_ForestCubes[i]->setWorld(XMMatrixScaling(0.1f, 0.1f, 0.1f) * XMMatrixTranslation(1.20f, 0.2f, -3.8f));
			this->m_LabyrinthCubes[i]->loadModel(CUBES_PATH1, this->device, this->context);
			this->m_LabyrinthCubes[i]->setWorld(XMMatrixScaling(0.1f, 0.1f, 0.1f) * XMMatrixTranslation(-8.4f, 0.3f, -.15f));

			//grön
			this->m_ForestPedestals[i]->loadModel(PEDI_PATH1, this->device, this->context);
			this->m_ForestPedestals[i]->setWorld(XMMatrixRotationX(-XM_PI / 2) * XMMatrixTranslation(-8.8f, -.8f, 1.5f));
			this->m_LabyrinthPedestals[i]->loadModel(PEDI_PATH1, this->device, this->context);
			this->m_LabyrinthPedestals[i]->setWorld(XMMatrixRotationX(-XM_PI / 2) * XMMatrixTranslation(-17.7277f, -.8f, 2.6197f));
		}
			break;
		case 2:
		{
			this->m_ForestCubes[i]->loadModel(CUBES_PATH2, this->device, this->context);
			this->m_ForestCubes[i]->setWorld(XMMatrixScaling(0.1f, 0.1f, 0.1f) * XMMatrixTranslation(-5.4f, 0.2f, 2.5f));
			this->m_LabyrinthCubes[i]->loadModel(CUBES_PATH2, this->device, this->context);
			this->m_LabyrinthCubes[i]->setWorld(XMMatrixScaling(0.1f, 0.1f, 0.1f) * XMMatrixTranslation(-8.4f, 0.3f, -.45f));

			//blå
			this->m_ForestPedestals[i]->loadModel(PEDI_PATH2, this->device, this->context);
			this->m_ForestPedestals[i]->setWorld(XMMatrixRotationX(-XM_PI / 2) * XMMatrixTranslation(-8.8f, -.8f, -2.5f));
			this->m_LabyrinthPedestals[i]->loadModel(PEDI_PATH2, this->device, this->context);
			this->m_LabyrinthPedestals[i]->setWorld(XMMatrixRotationX(-XM_PI / 2) * XMMatrixTranslation(-12.8989f, -.8f, -2.99004f));
		}
			break;
		case 3:
		{
			this->m_ForestCubes[i]->loadModel(CUBES_PATH3, this->device, this->context);
			this->m_ForestCubes[i]->setWorld(XMMatrixScaling(0.1f, 0.1f, 0.1f) * XMMatrixTranslation(-4.2f, 0.2f, -5.6f));
			this->m_LabyrinthCubes[i]->loadModel(CUBES_PATH3, this->device, this->context);
			this->m_LabyrinthCubes[i]->setWorld(XMMatrixScaling(0.1f, 0.1f, 0.1f) * XMMatrixTranslation(-8.4f, 0.3f, 0.45f));
			//gul
			this->m_ForestPedestals[i]->loadModel(PEDI_PATH3, this->device, this->context);
			this->m_ForestPedestals[i]->setWorld(XMMatrixRotationX(-XM_PI / 2) * XMMatrixTranslation(-8.8f, -.8f, -1.5f));
			this->m_LabyrinthPedestals[i]->loadModel(PEDI_PATH3, this->device, this->context);
			this->m_LabyrinthPedestals[i]->setWorld(XMMatrixRotationX(-XM_PI / 2) * XMMatrixTranslation(-11.3949f, -.8f, 1.4f));
		}
			break;
		}
	}

	return true;
}

bool CubeManager::checkPickUp()
{
	if (this->pPlayer->synchKey())
	{
		this->checkCollision();
	}
	return false;
}

void CubeManager::update()
{
	Dimension cDim = this->pPlayer->getCurrentDimension();
	PUZZLE_PHASE cPhase = this->pPlayer->getCurrentLevelPhase();
	
 	if (1)
	{
		switch (this->pPlayer->getCurrentDimension())
		{
		case Dimension::NORMAL:
			this->m_ForestCubes[0]->setSolid(false);
			this->m_ForestCubes[0]->setVisisble(false);
			this->m_ForestCubes[1]->setSolid(false);
			this->m_ForestCubes[1]->setVisisble(false);

			this->m_ForestCubes[2]->setSolid(true);
			this->m_ForestCubes[2]->setVisisble(true);
			this->m_ForestCubes[3]->setSolid(true);
			this->m_ForestCubes[3]->setVisisble(true);
			break;
		case Dimension::OTHER:
			this->m_ForestCubes[0]->setSolid(true);
			this->m_ForestCubes[0]->setVisisble(true);
			this->m_ForestCubes[1]->setSolid(true);
			this->m_ForestCubes[1]->setVisisble(true);

			this->m_ForestCubes[2]->setSolid(false);
			this->m_ForestCubes[2]->setVisisble(false);
			this->m_ForestCubes[3]->setSolid(false);
			this->m_ForestCubes[3]->setVisisble(false);
			break;
		}
	}
}

void CubeManager::Draw(DirectX::XMMATRIX in_Proj, DirectX::XMMATRIX in_View)
{

	this->context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->m_BasicShader->setBlendState();
	this->m_BasicShader->setDepthStencilState();
	this->m_BasicShader->setRasterizerState();
	this->m_BasicShader->setSamplerState();





	for (auto var : this->m_ForestCubes)
	{
		this->m_BasicShader->m_effect->SetMatrices(var->getWorld(), in_View, in_Proj);
		if (var->getVisisble())
		{
			var->Draw(this->context, in_View, in_Proj);
		}
	}
	for (auto var : this->m_LabyrinthCubes)
	{
		this->m_BasicShader->m_effect->SetMatrices(var->getWorld(), in_View, in_Proj);
		if (var->getVisisble())
		{
			var->Draw(this->context, in_View, in_Proj);
		}
	}
	for (auto var : this->m_LabyrinthPedestals)
	{
		this->m_BasicShader->m_effect->SetMatrices(var->getWorld(), in_View, in_Proj);
		if (var->getVisisble())
		{
			var->Draw(this->context, in_View, in_Proj);
		}
	}
	for (auto var : this->m_ForestPedestals)
	{
		this->m_BasicShader->m_effect->SetMatrices(var->getWorld(), in_View, in_Proj);
		if (var->getVisisble())
		{
			var->Draw(this->context, in_View, in_Proj);
		}
	}

}

int CubeManager::checkCollision()
{
	PUZZLE_PHASE cPhase = this->pPlayer->getCurrentLevelPhase();
	float distance = INFINITY; //some standard value
	XMVECTOR forwardVec = this->pPlayer->getCam()->getCamForward();
	XMVECTOR camPos = this->pPlayer->getCam()->getCamForward();
	
	switch (cPhase)
	{
	case FIRST:
		//check collisions with cubes for forest
		for (auto var : this->m_ForestCubes)
		{
			DirectX::BoundingBox box = var->getBoundingBox();

			camPos = DirectX::XMVector3Transform(camPos, DirectX::XMMatrixInverse(&DirectX::XMMatrixDeterminant(var->getWorld()), var->getWorld()));
			if (var->getSolid() && box.Intersects(camPos, forwardVec, distance))
			{
				//Intersects
				if (distance <= var->getGrabDistance())
				{
					//within range
					//add cube to inventory
					//setVisisble false
					var->setVisisble(false);
					//setSolid false
					var->setSolid(false);
				}
			}
		}
		break;
	case SECOND:
		//check collisions with cubes for labyrinth
		for (auto var : this->m_LabyrinthCubes)
		{
			DirectX::BoundingBox box = var->getBoundingBox();

			camPos = DirectX::XMVector3Transform(camPos, DirectX::XMMatrixInverse(&DirectX::XMMatrixDeterminant(var->getWorld()), var->getWorld()));
			if (var->getSolid() && box.Intersects(camPos, forwardVec, distance))
			{
				//Intersects
				if (distance <= var->getGrabDistance())
				{		
					//within range
					//add cube to inventory
					//setVisisble false
					var->setVisisble(false);
					//setSolid false
					var->setSolid(false);
				}
			}
		}
		break;
	}

	return -1;
}
