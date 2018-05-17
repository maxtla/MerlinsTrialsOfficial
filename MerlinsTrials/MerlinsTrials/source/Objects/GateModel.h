#pragma once
#ifndef GATE_MODEL_H
#define GATE_MODEL_H

#include "..\Importer\ObjectImporter.h"
#include "..\Shaders\BasicShader.h"
#include "..\Helpers\Timer.h"
#include "..\Helpers\Enumerators.h"
#include <vector>
#include <string>
#include "..\Levels\LevelState.h"
const std::string gateModelPath = ".//Assets//Models//Gate//Gate.fbx";

class GateModel
{
public:
	GateModel(BasicShader * ptr, LevelState * inLvl);
	~GateModel()
	{
		if (gateFrame)
			delete gateFrame;
		if (rightGate)
			delete rightGate;
		if (leftGate)
			delete leftGate;
	}
	
	bool loadModel(ID3D11Device* pDev, ID3D11DeviceContext * pDevCon);
	bool hasMeshesLoaded = false;
	bool getIsInAnimation() const;
	bool getIsOpen() const;
	float rotationSpeed = 17.0f;
	const float translationConstant = 1.44f;

	float angle = 0.0f;
	void setAnimation(const bool &in_value);
	bool checkCollision(BoundingOrientedBox &player);
	void Update();
	void Draw(Matrix view, Matrix projection);
private:
	Timer m_timer;
	bool isInAnimation = false;
	bool isOpen = false;

	Mesh* gateFrame = nullptr;
	Mesh* rightGate = nullptr;
	Mesh* leftGate = nullptr;

	Matrix frameMatrix = Matrix::CreateScale(0.0088) * Matrix::CreateRotationX(XM_PI * 0.5) * Matrix::CreateRotationY(XM_PI * -0.50) * Matrix::CreateTranslation(-9.25f, 0.24f, 0.07f);
	Matrix leftGateMatrix = Matrix::CreateScale(0.0088) * Matrix::CreateRotationX(XM_PI * 0.5) * Matrix::CreateRotationY(XM_PI * -0.50) * Matrix::CreateTranslation(-9.25f, 0.24f, 0.07f);
	Matrix rightGateMatrix = Matrix::CreateScale(0.0088) * Matrix::CreateRotationX(XM_PI * 0.5) * Matrix::CreateRotationY(XM_PI * -0.50) * Matrix::CreateTranslation(-9.25f, 0.24f, 0.07f);

	BoundingOrientedBox leftOBB;
	BoundingOrientedBox rightOBB;
	void transformOBB(BoundingOrientedBox &obb, Matrix transformation);

	BasicShader * m_BasicShader;
	LevelState * levelState;
	//debugstuff
	BasicShader * pDebugShader;
	std::unique_ptr<PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;
};





#endif