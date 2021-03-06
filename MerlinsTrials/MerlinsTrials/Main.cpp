// MerlinsTrialsOfficial.cpp : Defines the entry point for the application.
//

#include <d3d11.h>
#include "stdafx.h"
#include "Main.h"
#include "source\Window\Window.h"
#include "source\Managers\InputHandler.h"
#include "source\Engines\Direct3DEngine.h"
#include "source\Engines\Direct2DEngine.h"
#include "GeometricPrimitive.h"
#include "source\Managers\MenuManager.h"
#include "source\Levels\TEST_SCENE.h"


#define MAX_LOADSTRING 100

LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

//Global pointers
Window * pMainWindow;
Direct3DEngine * pD3DEngine = nullptr;
Direct2DEngine * pD2DEngine = nullptr;
MenuManager * pMenuManager = nullptr;
InputHandler * pInputHandler = nullptr;
TEST_SCENE * pTestScene = nullptr;

bool resolutionChanged = false;
bool run = true;
unsigned int state = STATES::IN_MENU;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Intialize the main window
	pMainWindow = new Window();
	pMainWindow->wndProc = wndProc;
	pMainWindow->LoadTitleAndClassName(hInstance);
	pMainWindow->MyRegisterClass(hInstance);
	pMainWindow->InitInstance(hInstance, nCmdShow);
	ShowWindow(pMainWindow->getHandler(), SW_SHOWMAXIMIZED);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MERLINSTRIALSOFFICIAL));
	
	//intialize the input handler
	pInputHandler = new InputHandler();
	pInputHandler->initialize(pMainWindow->getHandler());
	pD3DEngine = new Direct3DEngine();
	if (!pD3DEngine->initialize(pMainWindow->getHandler()))
		exit(-1);
	
	//set up a viewport (should probably move this into D3DEngine class anyway)
	D3D11_VIEWPORT vp;
	vp.Height = float(pMainWindow->getHeight());
	vp.Width = float(pMainWindow->getWidth());
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.MaxDepth = 1.0f;
	vp.MinDepth = 0.0f;
	
	pD3DEngine->setViewport(vp);

	//create the direct 2D engine
	pD2DEngine = new Direct2DEngine(pD3DEngine);

	//initalize the menu manager
	pMenuManager = new MenuManager();
	pMenuManager->initialize(pD2DEngine, pMainWindow->getHandler());
	

    // Main message loop:
    MSG msg;
    while (run)
    {
		pMainWindow->update(); //update window one frame later
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE) != 0)
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			if (msg.message == WM_KEYDOWN)
			{
				if (msg.wParam == VK_ESCAPE)
				{
					state = STATES::IN_MENU;
					pInputHandler->inMenu = true;
				}
			}
			pInputHandler->wndChanged(pMainWindow->windowChanged);
		}
		//reset D3DEngine before update and draw calls
		
		//update calls before draw calls
		pInputHandler->update();
		switch (state)
		{
		case STATES::IN_MENU:
			pD2DEngine->resetEngine();
			pInputHandler->inMenu = true;
			if (pMainWindow->windowChanged)
				pMenuManager->onResize();
			pMenuManager->Update(msg.message, state);
			pMenuManager->Draw();
			break;
		case STATES::START_GAME:
			if (pTestScene == nullptr)
			{
				pD2DEngine->resetEngine();
				pTestScene = new TEST_SCENE();
				pTestScene->Init(pD3DEngine, pInputHandler);
			}
			else
				state = STATES::IN_GAME;
			break;
		case STATES::IN_GAME:
			pD3DEngine->resetEngine();
			pInputHandler->inMenu = false;
			pTestScene->Update();
			pTestScene->Draw();
			break;
		case STATES::QUIT:
			delete pTestScene;
			pTestScene = nullptr;
			run = false;
		}
		//present final frame
		pD3DEngine->PresentFrame();
    }

	//free up all memory
	delete pD3DEngine;
	delete pInputHandler;
	delete pMainWindow;
	delete pD2DEngine;
	delete pMenuManager;
	delete pTestScene;

    return (int) msg.wParam;
}



//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(pMainWindow->getHInstance(), MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		run = false;
		break;
	case WM_ACTIVATEAPP:
		DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
		DirectX::Mouse::ProcessMessage(message, wParam, lParam);
		break;
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		DirectX::Mouse::ProcessMessage(message, wParam, lParam);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_F1)
		{
			unsigned int resolution[] = { R1024x600 };
			pMainWindow->setResolution( resolution );
			pD3DEngine->resize(hWnd);
		}
		if (wParam == VK_F2)
		{
			unsigned int resolution[] = { R1920x1080 };
			pMainWindow->setResolution(resolution);
			pD3DEngine->resize(hWnd);
		}
		if (wParam == VK_F3)
		{
			pMainWindow->enableFullscreen();
			pD3DEngine->setFullscreenState(true);
		}
		if (wParam == VK_F4)
		{
			pMainWindow->enableBordered();
			pD3DEngine->setFullscreenState(false);
		}
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
