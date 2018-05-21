#include "stdafx.h"
#include "LoadingScreen.h"
#include "..\Helpers\AssetsPaths.h"

void LoadingScreen::setLessStrength()
{
	DirectX::XMFLOAT4 vec(0.0f, 0.0f, 0.0f, 0.0f);
	this->fadeVec = DirectX::XMLoadFloat4(&vec);
	this->inc = 0.f;
}

void LoadingScreen::setFullStrength()
{
	DirectX::XMFLOAT4 vec(1.0f, 1.0f, 1.0f, 1.0f);
	this->fadeVec = DirectX::XMLoadFloat4(&vec);
	this->inc = 1.f;
}

void LoadingScreen::loadTexture()
{
	HRESULT hr;
	 hr = DirectX::CreateWICTextureFromFile(this->device, LOADING0, nullptr, &this->endTextureView);
	 if (FAILED(hr))
	 {
		 exit(-1);
	 }
	 hr = DirectX::CreateWICTextureFromFile(this->device, LOADING1, nullptr, &this->startTextureView);
	 if (FAILED(hr))
	 {
		 exit(-1);
	 }
}

float LoadingScreen::clamp(const float & in, const int & flag)
{
	if (flag)
	{
		if (in < -1.f)
		{
			return -1.f;
		}
	}
	else
	{
		if (in > 1.f)
		{
			return 1.f;
		}
	}
}

LoadingScreen::LoadingScreen(ID3D11Device * in_device, ID3D11DeviceContext * in_context, Player* in_player, LevelState* in_state)
{
	this->state = in_state;
	this->player = in_player;
	this->device = in_device;
	this->context = in_context;
	this->spriteBatch = std::make_unique<DirectX::SpriteBatch>(this->context);
	this->isFadingIn = false;
	this->isFadingOut = false;

	this->loadingSound = new SoundEngine();
	this->loadingSound->loadSound(FADE_SOUND_PATH);
}

LoadingScreen::~LoadingScreen()
{
	delete this->loadingSound;
}

void LoadingScreen::init()
{
	this->loadTexture();

	//texture covers entire screen rectangle
	this->rect.top = 0.f;
	this->rect.left = 0.f;
	this->rect.bottom = 1080.f;
	this->rect.right = 1920.f;
	DirectX::XMFLOAT4 vec(0, 0, 0, 0);
	this->fadeVec = DirectX::XMLoadFloat4(&vec);
}

void LoadingScreen::update()
{
	if (this->isFadingIn)
	{
		this->inc = this->fadeTimer.frameDiff() / 2000.f;
		if (inc >= 1.f)
		{
			this->fadeInFinished = true;
			this->isFadingIn = false;
			this->player->getCam()->setIsFloating(false);
			this->fadeTimer.reset();
		}
		else
		{
			XMFLOAT3 vecc = this->player->getCam()->getCamPos();
			
			this->player->getCam()->setCameraPosition(XMFLOAT3(vecc.x, vecc.y + inc / 10.f, vecc.z));
			DirectX::XMFLOAT4 vec(inc, inc, inc, inc);
			this->fadeVec = DirectX::XMLoadFloat4(&vec);
		}
	}
	if (this->isFadingOut)
	{
		this->inc -= this->fadeTimer.frameDiff() * std::pow(10, -5);
		if (inc <= 0.f)
		{

			this->isFadingOut = false;
			this->state->setIsEndScreen(false);
			this->fadeTimer.reset();
		}
		else
		{
			DirectX::XMFLOAT4 vec(inc, inc, inc, inc);
			this->fadeVec = DirectX::XMLoadFloat4(&vec);
		}
	}
}

void LoadingScreen::Draw()
{

	if (this->state->getIsEndScreen())
	{
		this->spriteBatch->Begin();

			if (this->isFadingIn)
			{
				this->spriteBatch->Draw(this->endTextureView, this->rect, this->fadeVec);
			}
			else
			{
				this->spriteBatch->Draw(this->startTextureView, this->rect, this->fadeVec);
			}
			
		this->spriteBatch->End();
	}



}

void LoadingScreen::startFade(const bool &fadingIn)
{
	if (fadingIn)
	{
		this->player->getCam()->setIsFloating(true);
		this->setLessStrength();
		this->isFadingIn = fadingIn;
		this->fadeTimer.startTimer();	
		this->loadingSound->playSound();
	}
	else
	{
		this->setFullStrength();
		this->isFadingOut = true;
		this->fadeTimer.startTimer();		
	}	
}

bool LoadingScreen::FadeFinished()
{
	return this->fadeInFinished;
}
