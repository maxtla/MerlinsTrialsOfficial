#include "stdafx.h"
#include "TEST_SCENE.h"


TEST_SCENE::TEST_SCENE()
{
}


TEST_SCENE::~TEST_SCENE()
{
}

void TEST_SCENE::Init(Direct3DEngine * p3DEngine, InputHandler * pInputHandler)
{
	this->pD3DEngine = p3DEngine;
	this->pInputHandler = pInputHandler;
	pCamera = new Camera();
	pCamera->createViewMatrix(Vector3(0.0f, 0.0f, -3.0f), Vector3(0.0f, 0.0f, 0.0f), DefaultUp);
	pCamera->createProjectionMatrix(DirectX::XM_PI * 45 / 180.f, 16 / 9.f, 0.01f, 100.f);
	pCamera->setCameraMoveSpeed(0.001f);
	pCamera->setRotationalOffset(0.001f);
	pCamera->setTimerCount(UNLIMITED);

	m_shape = DirectX::GeometricPrimitive::CreateTeapot(p3DEngine->pDevCon.Get(), 0.5f, 16U, true);
	m_world = DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XM_PI);
}

void TEST_SCENE::Update()
{
	pInputHandler->handleCameraInput(pCamera);
	pCamera->update();
}

void TEST_SCENE::Draw()
{
	m_shape->Draw(m_world, pCamera->getView(), pCamera->getProjection(), DirectX::Colors::Aquamarine);
}
