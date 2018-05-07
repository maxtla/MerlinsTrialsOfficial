#include "stdafx.h"
#include "CubeManager.h"

CubeManager::CubeManager()
{
}

CubeManager::~CubeManager()
{
}

bool CubeManager::initialize(std::vector<std::vector<Mesh*>> const &cubes, std::vector<Mesh*> const &pedestals,
	ID3D11DeviceContext * pDevCon, ID3D11Device * pDev, Camera* pCam, Interaction* pInteraction)
{
	this->context = pDevCon;
	this->device = pDev;
	this->pCam = pCam;
	this->pInteraction = pInteraction;

	m_BasicShader = new BasicShader();
	m_NormalMapShader = new NormalMapShader();

	m_BasicShader->init(pDev, pDevCon);
	m_BasicShader->createShader(SHADERTYPE::VertexPosNormCol);
	m_NormalMapShader->init(pDev, pDevCon);
	m_NormalMapShader->createShader(NORMALMAP_SHADER_TYPE::NO_COLOR);

	//update id between each new cube model, increment by one to fit cube vector position
	int id = 0;
	CubeModel * cModel = new CubeModel(DirectX::XMMatrixTranslation(1.0f, -10.0f, 1.0f), true, true, id);
	cModel->setMeshes(cubes[0]);
	cModel->setNormalMapShader(this->m_NormalMapShader);
	this->m_cubes.push_back(cModel);

	Matrix world = Matrix::CreateRotationZ(DirectX::XM_PI);
	PedestalModel * cPedestal = new PedestalModel(world * XMMatrixTranslation(0.0f, -10.0f, 0.0f), true, true, id);
	cPedestal->setMeshes(pedestals[0]);
	cPedestal->setBasicShader(m_BasicShader);
	this->m_pedestals.push_back(cPedestal);
	

	return true;
}

bool CubeManager::checkBoxPedestal()
{
	CubeModel* cModel = this->m_cubes[this->lastPickedCubeID];
	PedestalModel * pModel = this->m_pedestals[this->lastPickedCubeID];
	
	DirectX::XMMATRIX cXMM = cModel->getWorld();
	DirectX::XMMATRIX pXMM = pModel->getWorld();

	DirectX::BoundingOrientedBox cBox = cModel->getBoundingBox();
	DirectX::BoundingBox pBox = pModel->getBoundingBox();

	cBox.Transform(cBox, cXMM);
	pBox.Transform(pBox, pXMM);

	if (cBox.Intersects(pBox))
	{
		return true;
	}

	return false;
}

void CubeManager::update()
{
	//if E is pressed

	if (pInteraction->getEState())
	{
		switch (this->checkCollision())
		{
		case 0:
			this->updateCube(0);
			break;
		case 1:
			this->updateCube(1);
			break;
		case 2:
			this->updateCube(2);
			break;
		case 3:
			this->updateCube(3);
			break;
		case -1:
			pInteraction->setEState(false);
			break;
		}
	}

	if (pInteraction->getEState() && this->checkBoxPedestal())
	{
		pInteraction->setEState(false);
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

	for (auto var : this->m_pedestals)
	{
		var->Draw(this->context, in_View, in_Proj);
	}
}

void CubeManager::updateCube(const int & n)
{
	CubeModel * model = m_cubes[n];
	XMFLOAT3 xmf = pCam->getCamPos();
	//Vector3 vec3 = -pCam->getCamForward() * Vector3(5.f, 5.f, 5.f);
	//Vector3 vec = DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&vec3), DirectX::XMLoadFloat3(&xmf));
	Vector3 vec = Vector3(0.0f, 0.0f, -3.0f);

	XMMATRIX newW = XMMatrixIdentity();
	//XMMATRIX rot = XMMatrixRotationRollPitchYaw(this->pCam->getCamPitch(), 0.0f, 0.0f);
	XMMATRIX transl = XMMatrixTranslation(vec.x, vec.y, vec.z);
	XMMATRIX scale = XMMatrixIdentity(); //DirectX::XMMatrixScaling(0.3f, 0.3f, 0.3f);

	XMMATRIX invView = XMMatrixInverse(&XMMatrixDeterminant(this->pCam->getView()), this->pCam->getView());

	newW =  transl * invView;
	model->setWorldMatrix(newW);
}

int CubeManager::checkCollision()
{
	bool hit = false;
	float distance = INFINITY; //some standard value
	XMVECTOR forwardVec = this->pCam->getCamForward();
	XMVECTOR camPos = this->pCam->getCamPos();

	for (auto var : this->m_cubes)
	{
		DirectX::BoundingOrientedBox box = var->getBoundingBox();
		box.Transform(box, var->getWorld());
		//camPos = DirectX::XMVector3Transform(camPos, DirectX::XMMatrixInverse(&DirectX::XMMatrixDeterminant(var->getWorld()), var->getWorld()));
		if (box.Intersects(-camPos, forwardVec, distance))
		{
			//Intersects
			if (distance <= var->getGrabDistance())
			{
				//within range
				this->lastPickedCubeID = var->getID();
				return var->getID();
			}
		}
	}

	return -1;
}
