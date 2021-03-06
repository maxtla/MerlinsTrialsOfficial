#pragma once
#ifndef _BACKGROUND_H
#define _BACKGROUND_H

#include <d2d1_2.h>
#include <wrl\client.h>
#include <iostream>
#include "..\Engines\Direct2DEngine.h"

class Background
{
public:
	Background();
	~Background();
	void initialize(Direct2DEngine * ptr);

	void createBackgroundFromResource(PCWSTR resourceName, PCWSTR resourceType);
	void createBrushes(); //must be called AFTER resource has been loaded into bitmap
	void Draw();
	void onResize();
private:
	//rect to paint
	D2D1_RECT_F m_rectF;
	float width, height;
	D2D1::Matrix3x2F::D2D_MATRIX_3X2_F m_matrix;

	//COM
	Microsoft::WRL::ComPtr<ID2D1Bitmap> m_bitmap;
	Microsoft::WRL::ComPtr<ID2D1BitmapBrush1> m_bitmapBrush;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_basicBrush; //user this to draw the rectangle

	//2DEngine ptr
	Direct2DEngine * p2DEngine;
};
#endif // !BACKGROUND

