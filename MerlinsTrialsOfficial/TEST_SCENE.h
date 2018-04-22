#pragma once
#ifndef _TEST_SCENE_H
#define _TEST_SCENE_H

#include "source\Camera.h"
#include "source\InputHandler.h"
#include <GeometricPrimitive.h>
#include "source\Direct3DEngine.h"
#include <SimpleMath.h>

class TEST_SCENE
{
public:
	TEST_SCENE();
	~TEST_SCENE();
	void Init(Direct3DEngine * pEnginePtr, InputHandler * pInputHandler);
	void Update();
	void Draw();

private:
	Direct3DEngine * pD3DEngine;
	Camera * pCamera;
	InputHandler * pInputHandler;

	//geometry to render
	std::unique_ptr<DirectX::GeometricPrimitive> m_shape;
	DirectX::SimpleMath::Matrix m_world;
};

#endif // !_TEST_SCENE_H
