#include "stdafx.h"
#include "LevelManager.h"


LevelManager::LevelManager(Direct2DEngine * pD2D)
{
	this->pD2DEngine = pD2D;
	this->levelOne = new LevelOne(this->pD2DEngine);
	this->player = new Player();
}


LevelManager::~LevelManager()
{
	delete this->levelOne;
	delete this->player;
}

bool LevelManager::initGame(ID3D11Device * in_device, ID3D11DeviceContext * in_deviceContext, HWND hwnd)
{
	this->device = in_device;
	this->context = in_deviceContext;
	this->windowHandler = hwnd;
	this->gameStarted = true;
	this->changeLevel(this->currentLevel);
	return this->gameStarted;
}

void LevelManager::Update()
{
	this->levelOne->Update();
	if (this->levelOne->ResetLevel())
	{
		this->changeLevel(CURRENT_LEVEL::ONE);
	}
}

void LevelManager::Draw()
{
	this->levelOne->Draw();
}

void LevelManager::changeLevel(CURRENT_LEVEL nextlevel)
{
	if (this->levelOne != nullptr)
		delete this->levelOne;
	if(this->player != nullptr)
		delete this->player;
	switch (nextlevel)
	{
	case CURRENT_LEVEL::ONE: 
		this->player = new Player();
		this->levelOne = new LevelOne(this->pD2DEngine);
		if (!this->player->init(this->device, this->context, this->windowHandler))
			this->gameStarted = false;
		if (!this->levelOne->initialize(this->device, this->context, this->player))
			this->gameStarted = false;
		break;
	case  CURRENT_LEVEL::TWO:
		break;
	case  CURRENT_LEVEL::THREE:
		break;
	}
}
