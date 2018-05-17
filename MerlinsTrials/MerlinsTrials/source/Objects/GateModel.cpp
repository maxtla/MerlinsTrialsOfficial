#include "stdafx.h"
#include "GateModel.h"




GateModel::GateModel(BasicShader * ptr, LevelState * inLvl)
{
	this->m_BasicShader = ptr; 
	this->levelState = inLvl;
}

bool GateModel::loadModel(ID3D11Device* pDev, ID3D11DeviceContext * pDevCon)
{
	std::vector<Mesh*> m_Meshes;
	ObjectImporter m_Importer;
	int tryCounter = 0;
RetryPoint:
	if (!m_Importer.importFBXModel(gateModelPath, m_Meshes, pDev, pDevCon) && tryCounter < 5)
	{
		//flush vector and retry
		for (size_t i = 0; i < m_Meshes.size(); i++)
			delete m_Meshes[i];
		m_Meshes.clear();
		tryCounter++;
		goto RetryPoint;
	}
	else if (tryCounter >= 5)
		return false;

	if (m_Meshes.size() != 3)
		return false;
	else
	{
		for (size_t i = 0; i < m_Meshes.size(); i++)
		{
			if (m_Meshes[i]->getName() == "GateFrame")
			{
				this->gateFrame = m_Meshes[i];
			}
			if (m_Meshes[i]->getName() == "RightGate")
			{
				this->rightGate = m_Meshes[i];
				this->rightGate->createBoundingShapeFromType(AABB);
				this->rightGate->Update(rightGateMatrix);
			}
			if (m_Meshes[i]->getName() == "LeftGate")
			{
				this->leftGate = m_Meshes[i];
				this->leftGate->createBoundingShapeFromType(AABB);
				this->leftGate->Update(leftGateMatrix);
			}
		}
	}
	m_Meshes.clear();
#ifndef NDEBUG
	m_batch = std::make_unique<PrimitiveBatch<DirectX::VertexPositionColor>>(m_BasicShader->gDeviceContext);

	this->pDebugShader = new BasicShader();
	this->pDebugShader->init(m_BasicShader->gDevice, m_BasicShader->gDeviceContext);
	this->pDebugShader->createShader(VertexPosCol);
#endif
	return true;
}

bool GateModel::getIsInAnimation() const
{
	return this->isInAnimation;
}

bool GateModel::getIsOpen() const
{
	return this->isOpen;
}

void GateModel::Draw(Matrix view, Matrix projection)
{

	m_BasicShader->setBlendState(); //default
	m_BasicShader->setDepthStencilState(); //default
	m_BasicShader->setRasterizerState(); //default
	m_BasicShader->setSamplerState(); //default

	m_BasicShader->gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (gateFrame)
	{
		m_BasicShader->m_effect->SetMatrices(frameMatrix, view, projection);
		gateFrame->Draw(m_BasicShader);
	}
	if (leftGate)
	{
#ifndef NDEBUG
		//leftGate->m_OBB = leftOBB;
		leftGate->DrawDebugMode(pDebugShader, m_batch.get(), view, projection, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
#endif
		m_BasicShader->m_effect->SetMatrices(leftGateMatrix, view, projection);
		leftGate->Draw(m_BasicShader);
	}
	if (rightGate)
	{
#ifndef NDEBUG
		//rightGate->m_OBB = rightOBB;
		rightGate->DrawDebugMode(pDebugShader, m_batch.get(), view, projection, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
#endif
		m_BasicShader->m_effect->SetMatrices(rightGateMatrix, view, projection);
		rightGate->Draw(m_BasicShader);
	}
}

void GateModel::setAnimation(const bool & in_value)
{
	this->isInAnimation = in_value;
	m_timer.startTimer();
}

void GateModel::Update()
{
	if (!this->isOpen && !this->isInAnimation && levelState->getPhase() == PUZZLE_PHASE::SECOND)
	{
		this->setAnimation(true);
	}
	if (isInAnimation)
	{
		float deltaT = m_timer.frameDiff()/1000.0;
		float localangle = -rotationSpeed * deltaT;
		float translation = -rotationSpeed * translationConstant * deltaT;
		Matrix left = Matrix::CreateTranslation(0.0f, translation, 0.f) * Matrix::CreateRotationZ(-localangle * 0.0174532925f);
		Matrix right = Matrix::CreateTranslation(0.f, translation, 0.f) * Matrix::CreateRotationZ(localangle * 0.0174532925f);
		leftGateMatrix = left * leftGateMatrix;
		rightGateMatrix = right  * rightGateMatrix;
		
		leftGate->Update(left);
		rightGate->Update(right);

		angle += localangle;
		if (angle <= -120.f)
		{
			isInAnimation = false;
			isOpen = true;
		}
		m_timer.reset();
	}

	if (GetAsyncKeyState(KEY::G) && !isInAnimation)
	{
		isInAnimation = true;
		m_timer.startTimer();
	}
}

void GateModel::transformOBB(BoundingOrientedBox &obb, Matrix transformation)
{
	Vector3 scale = Vector3(1.f, 1.f, 1.f);
	Quaternion rotation;
	Vector3 translation;

	transformation.Decompose(scale, rotation, translation);

	Matrix trans = Matrix::CreateTranslation(translation) * Matrix::CreateScale(1.0f) * Matrix::CreateFromQuaternion(rotation);

	/*obb.Center = translation;
	obb.Extents = obb.Extents * scale;
	obb.Orientation = rotation;*/

	obb.Transform(obb, trans);
}