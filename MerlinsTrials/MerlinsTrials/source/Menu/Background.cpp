#include "stdafx.h"
#include "Background.h"


Background::Background()
{
}


Background::~Background()
{
	m_bitmap.Reset();
	m_bitmapBrush.Reset();
	m_basicBrush.Reset();
}

void Background::initialize(Direct2DEngine * ptr)
{
	p2DEngine = ptr;
	HWND hwnd = ::GetActiveWindow();
	RECT rect;
	if (::GetWindowRect(hwnd, &rect))
	{
		width = float(rect.right - rect.left);
		height = float(rect.bottom - rect.top);
		m_rectF.left = 0;
		m_rectF.right = 1920;
		m_rectF.top = 0;
		m_rectF.bottom = 1080;
		m_matrix = D2D1::Matrix3x2F::Scale(D2D1::SizeF(width / 1920, height / 1080), D2D1::Point2F(0, 0));
	}
	else
		throw std::runtime_error("ERROR: Unable to retrieve window rect.");
}

void Background::createBackgroundFromResource(PCWSTR resourceName, PCWSTR resourceType)
{
	HMODULE hModule = NULL;

	IWICBitmapDecoder *pDecoder = NULL;
	IWICBitmapFrameDecode *pSource = NULL;
	IWICStream *pStream = NULL;
	IWICFormatConverter *pConverter = NULL;
	IWICBitmapScaler *pScaler = NULL;

	HRSRC imageResHandle = NULL;
	HGLOBAL imageResDataHandle = NULL;
	void *pImageFile = NULL;
	DWORD imageFileSize = 0;

	//locate the resource
	imageResHandle = FindResourceW(hModule, resourceName, resourceType);
	HRESULT hr = imageResHandle ? S_OK : E_FAIL;
	if (SUCCEEDED(hr))
	{
		// Load the resource.
		imageResDataHandle = LoadResource(hModule, imageResHandle);

		hr = imageResDataHandle ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Lock it to get a system memory pointer.
		pImageFile = LockResource(imageResDataHandle);

		hr = pImageFile ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Calculate the size.
		imageFileSize = SizeofResource(hModule, imageResHandle);

		hr = imageFileSize ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Create a WIC stream to map onto the memory.
		hr = p2DEngine->getIWICImagingFactoryPtr()->CreateStream(&pStream);
	}
	if (SUCCEEDED(hr))
	{
		// Initialize the stream with the memory pointer and size.
		hr = pStream->InitializeFromMemory(
			reinterpret_cast<BYTE*>(pImageFile),
			imageFileSize
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create a decoder for the stream.
		hr = p2DEngine->getIWICImagingFactoryPtr()->CreateDecoderFromStream(
			pStream,
			NULL,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = p2DEngine->getIWICImagingFactoryPtr()->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	if (SUCCEEDED(hr))
	{
		//create a Direct2D bitmap from the WIC bitmap.
		hr = p2DEngine->getDeviceContextPtr()->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			&m_bitmap
		);

	}
	if (FAILED(hr))
		throw std::runtime_error("ERROR: Unable to create bitmap");

	pDecoder->Release();
	pSource->Release();
	pStream->Release();
	pConverter->Release();
	//pScaler->Release();

}

void Background::createBrushes()
{
	HRESULT hr = p2DEngine->getDeviceContextPtr()->
		CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 0.0f), &m_basicBrush);
	if (FAILED(hr))
		throw std::runtime_error("ERROR: Unable to create basic solid color brush.");
	hr = p2DEngine->getDeviceContextPtr()->CreateBitmapBrush(m_bitmap.Get(), &m_bitmapBrush);
	if (FAILED(hr))
		throw std::runtime_error("ERROR: Unable to create Bitmap brush.");
}

void Background::Draw()
{
	p2DEngine->getDeviceContextPtr()->BeginDraw();
	p2DEngine->getDeviceContextPtr()->FillRectangle(&m_rectF, m_bitmapBrush.Get());
	p2DEngine->getDeviceContextPtr()->SetTransform(D2D1::IdentityMatrix());
	p2DEngine->getDeviceContextPtr()->DrawRectangle(m_rectF, m_basicBrush.Get());
	if (FAILED(p2DEngine->getDeviceContextPtr()->EndDraw()))
		throw std::runtime_error("WARNING: Background draw call failed.");
}

void Background::onResize()
{
	HWND hwnd = ::GetActiveWindow();
	RECT rect;
	if (::GetWindowRect(hwnd, &rect))
	{
		width = float(rect.right - rect.left);
		height = float(rect.bottom - rect.top);
		m_matrix = D2D1::Matrix3x2F::Scale(D2D1::SizeF(width / 1920, height / 1080), D2D1::Point2F(0, 0));
	}
}
