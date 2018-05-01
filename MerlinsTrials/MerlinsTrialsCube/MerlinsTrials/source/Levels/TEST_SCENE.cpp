#include "stdafx.h"
#include "TEST_SCENE.h"


TEST_SCENE::TEST_SCENE()
{
}


TEST_SCENE::~TEST_SCENE()
{
	delete pMeshManager;
	delete pWallManager;
	delete pCamera;
	noCull->Release();
	pTextFormat->Release();
	pBrush->Release();
}

void TEST_SCENE::Init(Direct3DEngine * p3DEngine, Direct2DEngine * p2DEngine,InputHandler * pInputHandler)
{
	pMeshManager = new MeshManager();
	pWallManager = new WallManager();
	pCubeManager = new CubeManager();
	
	pMeshManager->initialize(p3DEngine->pDev.Get(), p3DEngine->pDevCon.Get());

	this->pD3DEngine = p3DEngine;
	this->pD2DEngine = p2DEngine;
	this->pInputHandler = pInputHandler;

	pCamera = new Camera();
	pCamera->createViewMatrix(Vector3(0.0f, 0.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f), DefaultUp);
	pCamera->createProjectionMatrix(DirectX::XM_PI * 45 / 180.f, 16 / 9.f, 0.01f, 100.f);
	pCamera->setCameraMoveSpeed(0.001f);
	pCamera->setRotationalOffset(0.001f);
	pCamera->setTimerCount(UNLIMITED);

	m_shape = DirectX::GeometricPrimitive::CreateTeapot(p3DEngine->pDevCon.Get(), 0.5f, 16U, true);
	m_world = DirectX::SimpleMath::Matrix::Identity;
	
	if (!pMeshManager->loadAllGeometry())
		exit(-1);
	if (!pWallManager->initialize(pMeshManager->getWalls(), p3DEngine->pDevCon.Get(), p3DEngine->pDev.Get()))
		exit(-1);
	if (!this->pCubeManager->initialize(this->pMeshManager->getWalls(), p3DEngine->pDevCon.Get(), p3DEngine->pDev.Get()))
		exit(-1);
	
	D3D11_RASTERIZER_DESC rsDesc;
	rsDesc.FillMode = D3D11_FILL_SOLID;
	rsDesc.CullMode = D3D11_CULL_NONE;
	rsDesc.FrontCounterClockwise = false;
	rsDesc.DepthBias = 0;
	rsDesc.SlopeScaledDepthBias = 0.0f;
	rsDesc.DepthBiasClamp = 0.0f;
	rsDesc.DepthClipEnable = true;
	rsDesc.ScissorEnable = false;
	rsDesc.MultisampleEnable = false;
	rsDesc.AntialiasedLineEnable = false;


	if (FAILED(p3DEngine->pDev.Get()->CreateRasterizerState(&rsDesc, &this->noCull)))
		exit(-1);

	p3DEngine->setRasterizerState(noCull);

	//text info stuff
	HRESULT hr = pD2DEngine->getWriteFactoryPtr()->CreateTextFormat(
		L"Gabriola",
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		16.f,
		L"sv_SV",
		&this->pTextFormat
	);
	if (FAILED(hr))
		throw std::runtime_error("ERROR: Unable to create text format.");

	hr = pD2DEngine->getDeviceContextPtr()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f), &pBrush);
	if (FAILED(hr))
		throw std::runtime_error("ERROR: Unable to create basic solid color brush.");
}

void TEST_SCENE::Update()
{
	pInputHandler->handleCameraInput(pCamera);
	pCamera->update();
	pWallManager->Update();
	this->pCubeManager->update();
}

void TEST_SCENE::Draw()
{
	m_shape->Draw(m_world, pCamera->getView(), pCamera->getProjection(), DirectX::Colors::Aquamarine);
	//pWallManager->Draw(pCamera->getProjection(), pCamera->getView());
	this->pCubeManager->Draw(this->pCamera->getProjection(), this->pCamera->getView());
	camInfoToScreen();
}

void TEST_SCENE::camInfoToScreen()
{
	std::wstring info = L"Camera Position:\nX: ";
	Vector3 pos = pCamera->getCamPos();
	info += std::to_wstring(pos.x) + L"\nY: " + std::to_wstring(pos.y) + L"\nZ: " + std::to_wstring(pos.z);
	D2D1_RECT_F rect;
	rect.top = rect.left = 50;
	rect.bottom = rect.right = 200;

	DirectX::BoundingOrientedBox box;
	box.Intersects(this->pCamera->getCamPos(), this->pCamera->getCamForward(), 20.0f);

	pD2DEngine->textToScreen(info, pTextFormat, &rect, pBrush);
}