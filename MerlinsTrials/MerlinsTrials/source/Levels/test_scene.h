#pragma once
#ifndef _TEST_SCENE_H
#define _TEST_SCENE_H

#include "..\Player\Camera.h"
#include <GeometricPrimitive.h>
#include "..\Engines\Direct3DEngine.h"
#include "..\Engines\Direct2DEngine.h"
#include "..\Managers\MeshManager.h"
#include "..\Managers\WallManager.h"
#include "..\Helpers\Timer.h"
#include "Level.h"
#include <d3d11.h>
#include <SimpleMath.h>

class TEST_SCENE
{
public:
	TEST_SCENE();
	~TEST_SCENE();
	void Init(Direct3DEngine * p3DEngine, Direct2DEngine * p2DEngine, HWND hwnd);
	void Update();
	void Draw();

private:
	Direct3DEngine * pD3DEngine;
	Direct2DEngine * pD2DEngine;
	MeshManager * pMeshManager;
	Camera * pCamera;
	WallManager * pWallManager;
	Level * levelOne;
	BasicShader * pBasicColorShader;

	//some stuff to render text info to screen
	unsigned int frameCounter = 0;
	unsigned int lastFrameCount = 0;
	Timer m_timer;
	IDWriteTextFormat * pTextFormat;
	ID2D1SolidColorBrush * pBrush;
	void camInfoToScreen();
	void FPStoScreen(unsigned int hertz);
};

#endif // !_TEST_SCENE_H
