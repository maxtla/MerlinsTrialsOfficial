#include "stdafx.h"
#include "Window.h"
#include "..\..\resource.h"

Window::Window()
{
}


Window::~Window()
{
	DestroyWindow(m_hwnd);
}

ATOM Window::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = this->wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MERLINSTRIALSOFFICIAL));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = m_mainWindowClassName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL Window::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	m_hInstance = hInstance;

	getDesktopResolution();

	m_hwnd = CreateWindowW(m_mainWindowClassName, m_title, WS_POPUP,
		m_pos_x, m_pos_y, m_width, m_height, nullptr, nullptr, hInstance, nullptr);

	::GetWindowRect(m_hwnd, &m_winRect);

	return TRUE;
}

void Window::LoadTitleAndClassName(HINSTANCE hInstance)
{
	LoadStringW(hInstance, IDS_APP_TITLE, m_title, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MERLINSTRIALSOFFICIAL, m_mainWindowClassName, MAX_LOADSTRING);
}

void Window::update()
{
	if (windowChanged)
		windowChanged = false; //we can assume that we updated all object to the new resolution at this point
}

void Window::setResolution(unsigned int resolution[])
{
	//adjust the position so the origin is relative to the screen center
	this->m_pos_x = unsigned int(screen_width - resolution[0]) * 0.5;
	this->m_pos_y = unsigned int(screen_height - resolution[1]) * 0.5;

	this->m_width = resolution[0];
	this->m_height = resolution[1];	

	::SetWindowPos(this->m_hwnd, 0, 
		m_pos_x, m_pos_y, 
		m_width, m_height,
		SWP_NOOWNERZORDER | SWP_NOZORDER);

	windowChanged = true;

}

void Window::enableFullscreen()
{
	if (!m_fullscreen)
	{
		m_fullscreen = true;
		m_bordered = false;
		SetWindowLong(m_hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
		windowChanged = true;
	}
}


void Window::enableBordered()
{
	if (!m_bordered)
	{
		m_bordered = true;
		m_fullscreen = false;
		SetWindowLong(m_hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
		windowChanged = true;
	}
}

void Window::getDesktopResolution()
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	screen_width = m_width = desktop.right;
	screen_height = m_height = desktop.bottom;
	m_pos_x = 0;
	m_pos_y = 0;
}

