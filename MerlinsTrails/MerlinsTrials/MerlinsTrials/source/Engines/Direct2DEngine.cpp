#include "stdafx.h"
#include "Direct2DEngine.h"


Direct2DEngine::Direct2DEngine(Direct3DEngine * pEngine) : pEngine(pEngine)
{
	try {
		create2DDevice();
		createBitmapRenderTarget();
		createImageFactory();
	}
	catch (std::exception &e)
	{
		OutputDebugString(convertStringToW(e.what()));
		exit(-1);
	}
}


Direct2DEngine::~Direct2DEngine()
{
	pWriteFactory.Reset();
	pFactory.Reset();
	p2DDev.Reset();
	p2DDevCon.Reset();
	pIWICFactory.Reset();
}


void Direct2DEngine::create2DDevice()
{
	//create the DirectWrite factory
	HRESULT hr;
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		&this->pWriteFactory);

	if (FAILED(hr))
		throw std::runtime_error("ERROR: Unable to create DirectWrite factory.");

	D2D1_FACTORY_OPTIONS options;

#ifndef NDEBUG
	options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#else
	options.debugLevel = D2D1_DEBUG_LEVEL_NONE;
#endif

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED,
		__uuidof(ID2D1Factory2),
		&options,
		&this->pFactory);

	if (FAILED(hr))
		throw std::runtime_error("ERROR: Unable to create Direct2D Factory.");

	//retrieve the dxgi device
	Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice;
	hr = pEngine->pDev->QueryInterface(__uuidof(IDXGIDevice), &dxgiDevice);

	if (FAILED(hr))
		throw std::runtime_error("ERROR: Unable to retrieve DXGI Device.");

	//create the Direct2D Device
	hr = pFactory->CreateDevice(dxgiDevice.Get(), &p2DDev);

	if (FAILED(hr))
		throw std::runtime_error("ERROR: Unable to create Direct2D Device.");

	hr = p2DDev->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS,
		&p2DDevCon);

	if (FAILED(hr))
		throw std::runtime_error("ERROR: Unable to create Direct2D DeviceContext.");

}

void Direct2DEngine::createBitmapRenderTarget()
{
	HRESULT hr;
	//set bitmap properties
	D2D1_BITMAP_PROPERTIES1 bitmapProperties;
	bitmapProperties.pixelFormat.format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bitmapProperties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
	bitmapProperties.dpiX = 0; //setting both dpiX and dpiY to 0 retrieves the desktop DPI setting
	bitmapProperties.dpiY = 0;
	bitmapProperties.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
	bitmapProperties.colorContext = nullptr;

	//retrieve the DXGI version of our backbuffer
	Microsoft::WRL::ComPtr<IDXGISurface> dxgiBuffer;
	hr = pEngine->m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), &dxgiBuffer);
	if (FAILED(hr))
		throw std::runtime_error("ERROR: Unable to retrieve backbuffer.");

	Microsoft::WRL::ComPtr<ID2D1Bitmap1> targetBitmap;
	hr = p2DDevCon->CreateBitmapFromDxgiSurface(dxgiBuffer.Get(), &bitmapProperties, &targetBitmap);
	if (FAILED(hr))
		throw std::runtime_error("ERROR: Unable to create Bitmap from DXGI Surface.");

	p2DDevCon->SetTarget(targetBitmap.Get());
}

void Direct2DEngine::createImageFactory()
{
	HRESULT hr;
	hr = CoInitialize(NULL);
	hr = CoCreateInstance(CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&pIWICFactory);

	if (FAILED(hr))
		throw std::runtime_error("ERROR: Unable to create WICImagingFactory.");
}


void Direct2DEngine::resetEngine()
{
	p2DDevCon->BeginDraw();
	p2DDevCon->Clear(D2D1::ColorF(D2D1::ColorF::Black, 1.0f));
	p2DDevCon->EndDraw();
}

wchar_t * Direct2DEngine::convertStringToW(const char * string)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, string, -1, wString, 4096);
	return wString;
}

void Direct2DEngine::textToScreen(std::wstring text, IDWriteTextFormat * textFormat, D2D1_RECT_F * layout, ID2D1SolidColorBrush * pBrush)
{
	p2DDevCon->BeginDraw();

	p2DDevCon->DrawTextW(text.c_str(), text.size(), textFormat, layout, pBrush);

	if (FAILED(p2DDevCon->EndDraw()))
		return;
}