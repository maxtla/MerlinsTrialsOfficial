#include "stdafx.h"
#include "MenuManager.h"


MenuManager::MenuManager()
{
}


MenuManager::~MenuManager()
{
	delete m_mainMenu;
}

void MenuManager::initialize(Direct2DEngine * p2DEngine, HWND hwnd)
{
	m_mainMenu = new MainMenu();
	m_mainMenu->initialize(p2DEngine, hwnd);
}

void MenuManager::Update(UINT msg, unsigned int &state)
{
	switch (currentMenu)
	{
	case MENUS::MAIN:
		m_mainMenu->Update(msg);
		break;
	case MENUS::OPTIONS:
		break;
	case MENUS::PAUSE:
		break;
	case MENUS::NONE:
		break;
	default:
		break;
	}
	if (m_mainMenu->startGame)
		state = STATES::START_GAME;
	else if (m_mainMenu->quit)
		state = STATES::QUIT;
}

void MenuManager::Draw()
{
	switch (currentMenu)
	{
	case MENUS::MAIN:
		m_mainMenu->Draw();
		break;
	case MENUS::OPTIONS:
		break;
	case MENUS::PAUSE:
		break;
	case MENUS::NONE:
		break;
	default:
		break;
	}
}

void MenuManager::onResize()
{
	//adjust every menu to the new resolution
	m_mainMenu->onResize();
}

void MenuManager::setCurrentMenu(MenuManager::MENUS menu)
{
	this->currentMenu = menu;
}
