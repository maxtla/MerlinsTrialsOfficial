#pragma once
#ifndef LEVELTIMER_H
#define LEVELTIMER_H
#include"..\Helpers\Timer.h"
#include"..\Levels\LevelState.h"
#include"SpriteFont.h"
#include"SimpleMath.h"

#define TIME_SECONDS 120;

class LevelTimer
{
private:
	Timer c_timer;
	ID3D11Device * m_device;
	ID3D11DeviceContext * m_context;
	LevelState * c_state;
	
	float m_timerDT;
	int m_timerSeconds;
	bool m_timerDone;
	bool m_timerActive;
	float m_drawStringRotation;
	DirectX::SimpleMath::Vector2 m_fontPos;
	DirectX::SimpleMath::Vector4 m_fontRedColor;
	DirectX::SimpleMath::Vector4 m_fontWhiteColor;
	DirectX::SimpleMath::Vector4 m_fontCurrentColor;
	DirectX::SimpleMath::Vector2 m_fontOrigin;	
	std::wstring m_drawString;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> m_font;

	void setDrawString(const std::wstring &in_str);
	void resetLevelTimer();
	void swapColor();
public:
	LevelTimer(ID3D11Device * in_device, ID3D11DeviceContext * in_context, LevelState * in_state);
	~LevelTimer();
	
	//SET
	void setTimer(const bool &in_value);
	
	//MISC
	void Draw();
	void update();

	//GET
	bool getIsActive() const;
	bool getIsDone() const;
};
#endif // !LEVELTIMER_H
