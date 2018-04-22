#include "stdafx.h"
#include "MainMenu.h"


MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
	delete m_startGame;
	delete m_options;
	delete m_quit;
	delete m_background;
}

void MainMenu::initialize(Direct2DEngine * p_2DEngine, HWND hwnd)
{
	p2DEngine = p_2DEngine;
	this->hwnd = hwnd;

	m_startGame = new Button(hwnd, L"START GAME", Vector2(200.f, 700.f));
	m_options = new Button(hwnd, L"OPTIONS", Vector2(200.f, 780.f));
	m_quit = new Button(hwnd, L"QUIT", Vector2(200.f, 860.f));

	m_background = new Background();

	try {
		m_startGame->createFormat(p2DEngine->getWriteFactoryPtr());
		m_startGame->createLayout(p2DEngine->getWriteFactoryPtr());
		m_startGame->createSolidColorBrush(p2DEngine->getDeviceContextPtr());
		m_startGame->createBitmapBrush(p2DEngine->getDeviceContextPtr(), p2DEngine->getIWICImagingFactoryPtr());

		m_options->createFormat(p2DEngine->getWriteFactoryPtr());
		m_options->createLayout(p2DEngine->getWriteFactoryPtr());
		m_options->createSolidColorBrush(p2DEngine->getDeviceContextPtr());
		m_options->createBitmapBrush(p2DEngine->getDeviceContextPtr(), p2DEngine->getIWICImagingFactoryPtr());

		m_quit->createFormat(p2DEngine->getWriteFactoryPtr());
		m_quit->createLayout(p2DEngine->getWriteFactoryPtr());
		m_quit->createSolidColorBrush(p2DEngine->getDeviceContextPtr());
		m_quit->createBitmapBrush(p2DEngine->getDeviceContextPtr(), p2DEngine->getIWICImagingFactoryPtr());

		PCWSTR resourceName = MAKEINTRESOURCE(IDB_MAIN_MENU_BGR);
		PCWSTR resourceType = L"PNG";

		m_background->initialize(p_2DEngine);
		m_background->createBackgroundFromResource(resourceName, resourceType);
		m_background->createBrushes();
	}
	catch (std::exception &e)
	{
		OutputDebugString(p2DEngine->convertStringToW(e.what()));
		exit(-1);
	}

}

void MainMenu::onResize()
{
}

void MainMenu::Update(UINT msg)
{
	startGame = m_startGame->Update(msg);
	openOptions = m_options->Update(msg);
	quit = m_quit->Update(msg);
}

void MainMenu::Draw()
{
	try {
		m_background->Draw();
		m_startGame->Draw(p2DEngine->getDeviceContextPtr());
		m_options->Draw(p2DEngine->getDeviceContextPtr());
		m_quit->Draw(p2DEngine->getDeviceContextPtr());
	}
	catch (std::exception &e)
	{
		OutputDebugString(p2DEngine->convertStringToW(e.what()));
	}
}
