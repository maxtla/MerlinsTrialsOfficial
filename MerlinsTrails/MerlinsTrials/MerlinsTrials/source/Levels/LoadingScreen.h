#pragma once
#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include<d3d11.h>
#include<WICTextureLoader.h>
#include<SpriteBatch.h>
#include<Windows.h>
#include"..\Window\Window.h"
#include"..\Helpers\Timer.h"
#include"..\Levels\LevelState.h"
#include"..\Player\Player.h"
#include "..\Engines\SoundEngine.h"

class LoadingScreen
{
private:
	ID3D11Device * device;
	ID3D11DeviceContext * context;
	ID3D11ShaderResourceView * endTextureView;
	ID3D11ShaderResourceView * startTextureView;

	LevelState * state;
	bool done = false;
	RECT rect;
	Timer fadeTimer;
	float inc = 0.f;
	float counter = 0.f;
	bool isFadingIn; //loading screen is incremented to full strenght
	bool isFadingOut; //loading screen is decreased till its not longer shown
	bool fadeInFinished = false;
	Player* player;
	DirectX::XMVECTOR fadeVec;
	std::unique_ptr<DirectX::SpriteBatch> spriteBatch;

	SoundEngine* loadingSound;

	void loadTexture();
	float clamp(const float &in, const int &flag);
public:
	LoadingScreen(ID3D11Device* in_device, ID3D11DeviceContext* in_context, Player * in_player, LevelState* in_state);
	~LoadingScreen();

	void init();
	void update();
	void Draw();

	void setLessStrength();
	void setFullStrength();
	void startFade(const bool &fadingIn);
	bool FadeFinished();

};
#endif // !LOADINGSCREEN_H
