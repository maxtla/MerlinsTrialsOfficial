//#include"LevelState.h"
#include"LevelOne.h"
#include"..\Helpers\Enumerators.h"
#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H
#include <d3d11.h>
#pragma once
class LevelManager
{
public:
	LevelManager(Direct2DEngine * pD2D);
	~LevelManager();
	bool initGame(ID3D11Device* in_device, ID3D11DeviceContext* in_deviceContext, HWND hwnd);
	void Update();
	void Draw();
	bool GameStarted() { return this->gameStarted; }
	void changeLevel(CURRENT_LEVEL nextlevel);
private:
	Direct2DEngine * pD2DEngine;
	ID3D11DeviceContext * context;
	HWND windowHandler;
	ID3D11Device * device;
	LevelOne* levelOne;
	Player* player;
	bool gameStarted = false;
	CURRENT_LEVEL currentLevel = CURRENT_LEVEL::ONE;
};

#endif