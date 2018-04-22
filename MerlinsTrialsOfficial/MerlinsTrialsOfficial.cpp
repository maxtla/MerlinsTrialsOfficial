// MerlinsTrialsOfficial.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MerlinsTrialsOfficial.h"
#include "source\InputHandler.h"
#include "source\GEngine.h"
#include "GeometricPrimitive.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MERLINSTRIALSOFFICIAL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MERLINSTRIALSOFFICIAL));

    MSG msg;

	// INPUT HANDLER TESTING
	InputHandler m_in;
	Camera m_cam;
	m_cam.createViewMatrix(Vector3(0.0f, 0.0f, 3.0f), Vector3(1.0f, 0.0f, 0.0f), DefaultUp);
	m_cam.setCameraMoveSpeed(0.01f);
	m_cam.setRotationalOffset(0.01f);
	GetMessage(&msg, nullptr, 0, 0);
	m_in.initialize(msg.hwnd);
	GEngine m_engine;
	if (!m_engine.initialize(msg.hwnd))
		exit(-1);
	std::unique_ptr<DirectX::GeometricPrimitive> shape;
	shape = DirectX::GeometricPrimitive::CreateTeapot(m_engine.pDevCon, 3.f, 8U, true);
	
	float width;
	float height;

	RECT rect;
	ZeroMemory(&rect, sizeof(RECT));
	if (GetWindowRect(msg.hwnd, &rect))
	{
		D3D11_VIEWPORT vp;
		vp.Height = width = rect.bottom - rect.top;
		vp.Width = height = rect.right - rect.left;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		vp.MaxDepth = 1.0f;
		vp.MinDepth = 0.0f;
	
		m_engine.setViewport(vp);

	}
	m_cam.createProjectionMatrix(DirectX::XM_PI*0.45f, (height / width), 0.01f, 100.f);
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
    // Main message loop:
    while (true)
    {
		if (GetMessage(&msg, nullptr, 0, 0))
		{
			m_in.handleCameraInput(&m_cam);
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			if (msg.message == WM_KEYDOWN)
			{
				if (msg.wParam == VK_ESCAPE)
				{
					break;
				}
			}

		}
		//reset engine
		m_engine.resetEngine();
		//draw the geometry 
		shape->Draw(
			world, 
			m_cam.getView(), 
			m_cam.getProjection(), 
			DirectX::Colors::CornflowerBlue, 
			nullptr, true);
		//output camera info to screen
		Vector3 pos = m_cam.getCamPos();
		std::wstring text = L"Position:\tX: " + std::to_wstring(pos.x) + L" Y: " + std::to_wstring(pos.y) + L" Z: " + std::to_wstring(pos.z);
		m_engine.textToScreen(text.c_str(), Vector2(50.f, 50.f), Vector2(0.5f, 0.5f));
		//present final frame
		m_engine.PresentFrame();
    }

	m_engine.Release();

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MERLINSTRIALSOFFICIAL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MERLINSTRIALSOFFICIAL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
		if (wParam == VK_ESCAPE)
		{
			DestroyWindow(hWnd);

			return 0;
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
