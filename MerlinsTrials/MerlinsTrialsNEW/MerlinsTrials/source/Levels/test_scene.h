#pragma once
#ifndef _TEST_SCENE_H
#define _TEST_SCENE_H

#include "..\Player\Camera.h"
#include "..\Managers\InputHandler.h"
#include <GeometricPrimitive.h>
#include "..\Engines\Direct3DEngine.h"
#include "..\Engines\Direct2DEngine.h"
#include "..\Managers\MeshManager.h"
#include "..\Managers\WallManager.h"
#include <d3d11.h>
#include <SimpleMath.h>

class TEST_SCENE
{
public:
	TEST_SCENE();
	~TEST_SCENE();
	void Init(Direct3DEngine * p3DEngine, Direct2DEngine * p2DEngine, InputHandler * pInputHandler);
	void Update();
	void Draw();

private:
	Direct3DEngine * pD3DEngine;
	Direct2DEngine * pD2DEngine;
	MeshManager * pMeshManager;
	Camera * pCamera;
	InputHandler * pInputHandler;
	WallManager * pWallManager;
	ID3D11RasterizerState * noCull;

	//geometry to render
	std::unique_ptr<DirectX::GeometricPrimitive> m_shape;
	DirectX::SimpleMath::Matrix m_world;

	//some stuff to render text info to screen
	IDWriteTextFormat * pTextFormat;
	ID2D1SolidColorBrush * pBrush;
	void camInfoToScreen();
};

#endif // !_TEST_SCENE_H
