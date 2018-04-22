#pragma once
#pragma comment(lib, "Dwrite.lib")
#pragma comment(lib, "D2d1.lib")
//#ifndef _DIRECT2DENGINE_H
//#define _DIRECT2DENGINE_H

#include <d2d1_2.h>
#include <dwrite_2.h>
#include <wrl/client.h>
#include "source/Direct3DEngine.h"
#include <string.h>
#include <iostream>
#include <wincodec.h>

class Direct2DEngine
{
public:
	Direct2DEngine(Direct3DEngine * pEngine);
	~Direct2DEngine();
	//get functions
	IDWriteFactory2* getWriteFactoryPtr() const { return pWriteFactory.Get(); }
	ID2D1Factory2* getFactoryPtr() const { return pFactory.Get(); }
	ID2D1Device1* getDevicePtr() const { return p2DDev.Get(); }
	ID2D1DeviceContext1* getDeviceContextPtr() const { return p2DDevCon.Get(); }
	IWICImagingFactory* getIWICImagingFactoryPtr() const { return pIWICFactory.Get(); }
	
	//helper function (should really create a helper Header file)
	wchar_t* convertStringToW(const char* string);
private:
	Direct3DEngine * pEngine;

	Microsoft::WRL::ComPtr<IDWriteFactory2>  pWriteFactory;
	Microsoft::WRL::ComPtr<ID2D1Factory2>  pFactory;
	Microsoft::WRL::ComPtr<ID2D1Device1>  p2DDev;
	Microsoft::WRL::ComPtr<ID2D1DeviceContext1> p2DDevCon;
	Microsoft::WRL::ComPtr<IWICImagingFactory> pIWICFactory;

	void create2DDevice();
	void createBitmapRenderTarget();
	void createImageFactory();
};
//#endif //!_DIRECT2DENGINE_H
