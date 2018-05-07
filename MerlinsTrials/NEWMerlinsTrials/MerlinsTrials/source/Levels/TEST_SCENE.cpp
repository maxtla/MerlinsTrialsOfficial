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
	delete levelOne;
	delete pBasicColorShader;
	pTextFormat->Release();
	pBrush->Release();
}

void TEST_SCENE::Init(Direct3DEngine * p3DEngine, Direct2DEngine * p2DEngine, HWND hwnd)
{
	pMeshManager = new MeshManager();
	pWallManager = new WallManager();
	levelOne = new Level();
	pMeshManager->initialize(p3DEngine->pDev.Get(), p3DEngine->pDevCon.Get());

	this->pD3DEngine = p3DEngine;
	this->pD2DEngine = p2DEngine;

	pBasicColorShader = new BasicShader();
	pBasicColorShader->init(p3DEngine->pDev.Get(), p3DEngine->pDevCon.Get());
	pBasicColorShader->createShader(SHADERTYPE::VertexPosNormCol);

	pCamera = new Camera();
	pCamera->createViewMatrix(Vector3(0.0f, 0.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f), DefaultUp);
	pCamera->createProjectionMatrix(DirectX::XM_PI * 45 / 180.f, 16 / 9.f, 0.01f, 100.f);
	pCamera->setCameraMoveSpeed(0.0088f);
	pCamera->setRotationalOffset(0.0001f);
	pCamera->setTimerCount(UNLIMITED);
	pCamera->init(hwnd);

ReloadPoint:
	if (!pMeshManager->loadAllGeometry())
	{
		pMeshManager->flush();
		OutputDebugStringA("ERROR LOADING IN GEOMETRY - TRYING AGAIN\n");
		goto ReloadPoint;
	}

	if (!pWallManager->initialize(pMeshManager->getWalls(), p3DEngine->pDevCon.Get(), p3DEngine->pDev.Get()))
		exit(-1);

	if (!levelOne->initialize(pMeshManager->getStaticLevels()[0], pBasicColorShader))
		exit(-1);

	//text info stuff
	HRESULT hr = pD2DEngine->getWriteFactoryPtr()->CreateTextFormat(
		L"Gabriola",
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		32.f,
		L"sv_SV",
		&this->pTextFormat
	);
	if (FAILED(hr))
		throw std::runtime_error("ERROR: Unable to create text format.");

	hr = pD2DEngine->getDeviceContextPtr()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f), &pBrush);
	if (FAILED(hr))
		throw std::runtime_error("ERROR: Unable to create basic solid color brush.");

	m_timer.startTimer();
}

void TEST_SCENE::Update()
{
	//pInputHandler->handleCameraInput(pCamera);
	pCamera->update();
	pWallManager->Update();
	levelOne->Update();
}

void TEST_SCENE::Draw()
{
	//pWallManager->Draw(pCamera->getView(), pCamera->getProjection());
	levelOne->Draw(pCamera->getView(), pCamera->getProjection());
	camInfoToScreen();
	this->FPStoScreen(lastFrameCount);
	if (m_timer.frameDiff() >= 1000.0)
	{
		lastFrameCount = frameCounter;
		frameCounter = 0;
		m_timer.reset();
	}
	frameCounter++;
}

void TEST_SCENE::camInfoToScreen()
{
	std::wstring info = L"Camera Position:\nX: ";
	Vector3 pos = pCamera->getCamPos();
	info += std::to_wstring(pos.x) + L"\nY: " + std::to_wstring(pos.y) + L"\nZ: " + std::to_wstring(pos.z);
	D2D1_RECT_F rect;
	rect.top = rect.left = 50;
	rect.bottom = rect.right = 400;

	pD2DEngine->textToScreen(info, pTextFormat, &rect, pBrush);
}

void TEST_SCENE::FPStoScreen(unsigned int hertz)
{
	std::wstring info = L"FPS: ";
	info += std::to_wstring(hertz);
	D2D1_RECT_F rect;
	rect.top = 320; 
	rect.left = 50;
	rect.bottom = 400;
	rect.right = 200;

	pD2DEngine->textToScreen(info, pTextFormat, &rect, pBrush);
}