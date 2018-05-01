#pragma once
#ifndef _MAIN_MENU_H
#define _MAIN_MENU_H

#include "Button.h"
#include "Background.h"
#include "..\Engines\Direct2DEngine.h"

class MainMenu
{
public:
	MainMenu();
	~MainMenu();
	void initialize(Direct2DEngine * m_2DEngine, HWND hwnd);
	void onResize();

	void Update(UINT msg);
	void Draw();

	bool startGame = false;
	bool openOptions = false;
	bool quit = false;
private:
	Button * m_startGame = nullptr;
	Button * m_options = nullptr;
	Button * m_quit = nullptr;

	Background * m_background = nullptr;
	//save the 2D engine ptr and the main window handler,
	//we neeed them for rendering and onResize events.
	Direct2DEngine * p2DEngine;
	HWND hwnd;

};
#endif // !_MAIN_MENU_H

