#pragma once
#pragma comment(lib, "Windowscodecs.lib")

#ifndef BUTTON_H
#define BUTTON_H
#include <d2d1_2.h>
#include <d3d11.h>
#include <dwrite_2.h>
#include <dwrite.h>
#include <SimpleMath.h>
#include <wrl\client.h>
#include <iostream>
#include <Windows.h>
#include <wincodec.h>
#include "resource.h"

#define BUTTON_WIDTH 1024
#define BUTTON_HEIGHT 55
#define BUTTON_SCALING_X 1920
#define BUTTON_SCALING_Y 1080

using namespace DirectX::SimpleMath;

class Button
{
public:
	Button(HWND hwnd, std::wstring content = L"UNDEFINED", Vector2 pos = Vector2::Zero);
	~Button();
	void createFormat(
		IDWriteFactory2* factory,
		const WCHAR* font = L"Gabriola",
		IDWriteFontCollection* fontCollection = nullptr,
		DWRITE_FONT_WEIGHT fontWeight = DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE fontStyle = DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH fontStretch = DWRITE_FONT_STRETCH_NORMAL,
		float fontSize = 30.0f,
		const WCHAR* localeName = L"sv_SV");
	void createLayout(IDWriteFactory2* factory);
	void createSolidColorBrush(ID2D1DeviceContext1* p2DDevCon, D2D1::ColorF color = D2D1::ColorF::White);
	void createBitmapBrush(ID2D1DeviceContext1* p2DDevCon, IWICImagingFactory* pWICFactory);

	bool Update(UINT msg);
	void Draw(ID2D1DeviceContext1* p2DDevCon);
	void onResize();
private:
	std::wstring m_content;
	HWND m_hwnd; //save the window handler for resize events

	Microsoft::WRL::ComPtr<IDWriteTextFormat> m_format;
	Microsoft::WRL::ComPtr<IDWriteTextLayout> m_layout;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_colorBrush; //Use this to draw the text inside the rectangle
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_basicBrush; //user this to draw the rectangle
	Microsoft::WRL::ComPtr<ID2D1BitmapBrush1> m_bitmapBrush; //use this if we want to draw a texture inside the rectangle
	Microsoft::WRL::ComPtr<ID2D1Bitmap> m_bitmap; //this stores the texture in a bitmap

	Vector2 m_Position;
	D2D1_SIZE_F m_scaling;
	D2D1_SIZE_F m_TextScaling;
	RECT m_winRect;
	D2D1_RECT_F m_rect;
	D2D1_POINT_2F m_origin;

	bool isPressed = false;

	//methods for image loading
	void LoadResourceBitmap(ID2D1DeviceContext1* p2DDevCon, IWICImagingFactory* pWICFactory);
	void prepareRectPos();
};
#endif // !BUTTON_H

