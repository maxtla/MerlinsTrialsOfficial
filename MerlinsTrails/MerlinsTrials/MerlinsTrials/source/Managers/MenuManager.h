#pragma once
#ifndef _MENU_MANAGER_H
#define _MENU_MANAGER_H
#include "..\Menu\MainMenu.h"

enum STATES
{
	IN_MENU,
	START_GAME,
	IN_GAME,
	QUIT
};

class MenuManager
{
public:
	enum MENUS
	{
		MAIN = 0,
		OPTIONS = 1,
		PAUSE = 2,
		NONE = 3
	};
	MenuManager();
	~MenuManager();
	void initialize(Direct2DEngine * p2DEngine, HWND hwnd);
	void Update(UINT msg, unsigned int &state);
	void Draw();
	void onResize();

	void setCurrentMenu(MenuManager::MENUS menu);
private:
	unsigned int currentMenu = MENUS::MAIN;
	//menu ptrs
	MainMenu * m_mainMenu = nullptr;
};
#endif // !_MENU_MANAGER_H

