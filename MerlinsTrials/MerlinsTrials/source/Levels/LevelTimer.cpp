#include "stdafx.h"
#include "LevelTimer.h"
#include "..\Helpers\AssetsPaths.h"

LevelTimer::LevelTimer(ID3D11Device* in_device, ID3D11DeviceContext * in_context, LevelState * in_state)
{
	this->m_context = in_context;
	this->m_device = in_device;
	this->c_state = in_state;
	this->c_timer = Timer();

	this->m_font = std::make_unique<DirectX::SpriteFont>(this->m_device, FONT_PATH);
	this->m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(this->m_context);
	this->m_fontPos = DirectX::SimpleMath::Vector2(960.f, 100.f);
	this->m_fontCurrentColor = DirectX::SimpleMath::Vector4(DirectX::Colors::Green);
	this->m_drawStringRotation = 0.f;
	this->m_drawString = std::wstring(L"IF THIS IS VISIBLE - SOMETHING FAILED");
	this->m_timerSeconds = TIME_SECONDS  ;
	this->m_timerDT = 0.f;
	this->m_timerActive = false;
}

LevelTimer::~LevelTimer()
{
}

void LevelTimer::setTimer(const bool & in_value)
{
	if (in_value)
	{
		this->m_timerActive = in_value;
		this->c_timer.reset();
		this->setDrawString(std::to_wstring(this->m_timerSeconds));
		return; //exit function
	}
	else
	{
		this->resetLevelTimer();
	}

}

void LevelTimer::setDrawString(const std::wstring &in_str)
{
	this->m_drawString = in_str;
	this->m_fontOrigin = m_font->MeasureString(this->m_drawString.c_str());
	this->m_fontOrigin *= 0.5f;
}

void LevelTimer::resetLevelTimer()
{
	this->m_timerSeconds = TIME_SECONDS;
	this->m_timerActive = false;
	this->setDrawString(std::to_wstring(this->m_timerSeconds));
}

void LevelTimer::swapColor()
{
	switch (this->m_timerSeconds)
	{
	case 120:
		this->m_fontCurrentColor = DirectX::SimpleMath::Vector4(DirectX::Colors::White);
		break;
	case 60:
		this->m_fontCurrentColor = DirectX::SimpleMath::Vector4(DirectX::Colors::Yellow);
		break;
	case 30:
		this->m_fontCurrentColor = DirectX::SimpleMath::Vector4(DirectX::Colors::Red);
		break;
	}
}

void LevelTimer::Draw()
{
	switch (this->c_state->getTimer())
	{
	case TIMER::START:
		this->m_spriteBatch->Begin();

		this->m_font->DrawString(this->m_spriteBatch.get(), this->m_drawString.c_str(),
			this->m_fontPos, this->m_fontCurrentColor,
			this->m_drawStringRotation, this->m_fontOrigin);

		this->m_spriteBatch->End();
		break;
	default:
		//why not
		break;
	}

}

void LevelTimer::update()
{
	if (this->m_timerActive)
	{

		this->m_timerDT += (this->c_timer.frameDiff() / 1000.f);

		if (this->m_timerDT >= 1.0f)
		{
			this->swapColor();
			this->m_timerSeconds -= 1;
			this->setDrawString(std::to_wstring(this->m_timerSeconds));
			this->m_timerDT = 0.0f;
		}
		if (this->m_timerSeconds == 0)
		{
			//when the timer hits 0
			this->setTimer(false);
			this->c_state->setTimer(TIMER::STOP);
		}

		this->c_timer.reset();
	}
	if (GetAsyncKeyState(KEY::C) && !m_timerActive)
	{
		this->setTimer(true);
	}
}

bool LevelTimer::getIsActive() const
{
	return this->m_timerActive;
}

bool LevelTimer::getIsDone() const
{
	return this->m_timerDone;
}
