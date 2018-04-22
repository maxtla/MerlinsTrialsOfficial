#include "stdafx.h"
#include "Button.h"


Button::Button(HWND hwnd, std::wstring content, Vector2 pos)
{
	m_content = content;

	//should be hardcoded
	m_rect = D2D1::RectF(0, 0, BUTTON_WIDTH, BUTTON_HEIGHT); 
	//should be dependent on the current screen resolution for correct scaling
	//take the screen width and normalize it, same with the height. this should become 
	//used as an offset factor
	RECT windowRes;
	if (::GetWindowRect(hwnd, &windowRes))
	{
		float x_scaling, y_scaling;
		x_scaling = float(windowRes.right / BUTTON_SCALING_X) * 0.3f;
		y_scaling = float(windowRes.bottom / BUTTON_SCALING_Y);
		m_origin = D2D1::Point2F(pos.x, pos.y);
		m_scaling = D2D1::SizeF(x_scaling, y_scaling);
		m_winRect.left = LONG(pos.x);
		m_winRect.top = LONG(pos.y);
		m_winRect.right = LONG((pos.x + BUTTON_WIDTH * x_scaling));
		m_winRect.bottom = LONG((pos.y + BUTTON_HEIGHT * y_scaling));

	}
}


Button::~Button()
{
	m_format.Reset();
	m_layout.Reset();
	m_colorBrush.Reset();
	m_basicBrush.Reset();
	m_bitmapBrush.Reset();
	m_bitmap.Reset();
}

void Button::createFormat(IDWriteFactory2 * factory, const WCHAR * font, IDWriteFontCollection * fontCollection, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, float fontSize, const WCHAR * localeName)
{
	HRESULT hr = factory->CreateTextFormat(
		font,
		fontCollection,
		fontWeight,
		fontStyle,
		fontStretch,
		fontSize,
		localeName,
		&this->m_format
	);
	if (FAILED(hr))
		throw std::runtime_error("ERROR: Unable to create text format.");
}

void Button::createLayout(IDWriteFactory2 * factory)
{
	if (m_format == nullptr)
		throw std::runtime_error("ERROR: Unable to create text layout. TextFormat was nullptr."); //this should be impossible

	HRESULT hr = factory->CreateTextLayout(
		m_content.c_str(),
		(UINT32)m_content.length(),
		m_format.Get(),
		BUTTON_WIDTH * m_scaling.width,
		BUTTON_HEIGHT * m_scaling.height,
		&m_layout
	);
	if (FAILED(hr))
		throw std::runtime_error("ERROR: Unable to create text layout.");
}

void Button::createSolidColorBrush(ID2D1DeviceContext1* p2DDevCon, D2D1::ColorF color)
{
	HRESULT hr = p2DDevCon->CreateSolidColorBrush(color, &m_colorBrush);
	if (FAILED(hr))
		throw std::runtime_error("ERROR: Unable to create custom solid color brush.");
	hr = p2DDevCon->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 0.0f), &m_basicBrush);
	if (FAILED(hr))
		throw std::runtime_error("ERROR: Unable to create basic solid color brush.");
}

void Button::createBitmapBrush(ID2D1DeviceContext1 * p2DDevCon, IWICImagingFactory * pWICFactory)
{
	try {
		LoadResourceBitmap(p2DDevCon, pWICFactory);
	}
	catch (std::exception &e)
	{
		throw std::runtime_error(e.what());
	}
	HRESULT hr = p2DDevCon->CreateBitmapBrush(m_bitmap.Get(), &m_bitmapBrush);
	if (FAILED(hr))
		throw std::runtime_error("ERROR: Unable to create Bitmap brush.");

}

bool Button::Update(UINT msg)
{

	POINT mousePos;
	GetCursorPos(&mousePos);

	if (msg == WM_LBUTTONDOWN)
	{
		if (PtInRect(&m_winRect, mousePos))
			isPressed = true;
	}
	if (msg == WM_LBUTTONUP)
	{
		isPressed = false;
		if (PtInRect(&m_winRect, mousePos))
		{
			return true;
		}
	}
	if (isPressed)
	{
		m_colorBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black, 1.0f));
		m_rect.top = BUTTON_HEIGHT;
		m_rect.bottom = m_rect.top + BUTTON_HEIGHT;
	}
	else if (PtInRect(&m_winRect, mousePos) && !isPressed)
	{
		m_colorBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black, 1.0f));
		m_rect.top = 130;
		m_rect.bottom = m_rect.top + BUTTON_HEIGHT;
	}
	else
	{
		m_colorBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White, 1.0f));
		m_rect.top = 0;
		m_rect.bottom = BUTTON_HEIGHT;
	}

	return false;
}

void Button::Draw(ID2D1DeviceContext1 * p2DDevCon)
{
	p2DDevCon->BeginDraw();
	p2DDevCon->SetTransform(D2D1::Matrix3x2F::Translation(D2D1::SizeF(m_origin.x, m_origin.y - m_rect.top)) * D2D1::Matrix3x2F::Scale(m_scaling, m_origin));
	p2DDevCon->FillRectangle(&m_rect, m_bitmapBrush.Get());
	p2DDevCon->DrawRectangle(m_rect, m_basicBrush.Get());
	D2D1_POINT_2F centered = D2D1::Point2F(m_origin.x + (m_winRect.right * 0.25) - m_content.length()*4, m_origin.y - BUTTON_HEIGHT * 0.1);
	p2DDevCon->SetTransform(D2D1::IdentityMatrix());
	p2DDevCon->DrawTextLayout(centered, m_layout.Get(), m_colorBrush.Get());
	if (FAILED(p2DDevCon->EndDraw()))
		throw std::runtime_error("WARNING: Button draw call failed.");
}

void Button::LoadResourceBitmap(ID2D1DeviceContext1 * p2DDevCon, IWICImagingFactory * pWICFactory)
{
	PCWSTR resourceName = MAKEINTRESOURCE(IDB_MENU_BUTTONS);
	PCWSTR resourceType = L"PNG"; //we use a custom type so we must specify it
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
		hr = pWICFactory->CreateStream(&pStream);
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
		hr = pWICFactory->CreateDecoderFromStream(
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
		hr = pWICFactory->CreateFormatConverter(&pConverter);
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
		hr = p2DDevCon->CreateBitmapFromWicBitmap(
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

