#pragma once

#include "Keyboard.h"
#include "Mouse.h"

//dessa macros fungerar som en array: int resolution[2] = MACRONAME
#define R1024x600 1024 , 600
#define R1280x720 1280 , 720
#define R1366x768 1366 , 768
#define R1600x900 1600 , 900
#define R1920x1080 1920 , 1080
#define R2560x1440 2560 , 1440

#ifndef WINDOW_H
#define WINDOW_H
#define MAX_LOADSTRING 100

#include <string>
#include "Resource.h"

class Window
{
public:
	Window();
	~Window();
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
	void LoadTitleAndClassName(HINSTANCE hInstance);
	bool windowChanged = false;
	//get functions
	HINSTANCE getHInstance() const { return m_hInstance; }
	HWND getHandler() const { return m_hwnd; }
	unsigned int getWidth() const { return m_width; }
	unsigned int getHeight() const { return m_height; }
	WNDPROC wndProc;
	void update();

	//set functions
	void setResolution(unsigned int resolution[]);
	void enableFullscreen();
	void enableBordered();

private:
	HINSTANCE m_hInstance;
	HWND m_hwnd;

	WCHAR m_title[MAX_LOADSTRING];
	WCHAR m_mainWindowClassName[MAX_LOADSTRING];

	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_pos_x;
	unsigned int m_pos_y;
	RECT m_winRect;

	unsigned int screen_width;
	unsigned int screen_height;

	bool m_fullscreen = true;
	bool m_bordered = false;

	//PRIVATE HELPER METHODS
	void getDesktopResolution();
};
#endif // !WINDOW_H

