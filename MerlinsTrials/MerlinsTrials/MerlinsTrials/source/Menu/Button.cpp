#include "stdafx.h"
#include "Button.h"


Button::Button(HWND hwnd, std::wstring content, Vector2 pos)
{
	m_content = content;
	m_hwnd = hwnd;
	m_Position = pos;
	//should be hardcoded
	//should be dependent on the current screen resolution for correct scaling
	//take the screen width and normalize it, same with the height. this should become 
	//used as an offset factor
	RECT windowRes;
	if (::GetWindowRect(hwnd, &windowRes))
	{
		//calculate the width and height of the window
		float width = float(windowRes.right - windowRes.left);
		float height = float(windowRes.bottom - windowRes.top);
		float offset_x = width / BUTTON_SCALING_X;
		float offset_y = height / BUTTON_SCALING_Y;
		m_TextScaling = D2D1::SizeF(offset_x, offset_y);
		//place the button based on the offset values
		m_winRect.left = windowRes.left + (pos.x * offset_x);
		m_winRect.top = windowRes.top + (pos.y * offset_y);
		//calculate the scaling
		m_scaling = D2D1::SizeF(offset_x * 0.3, offset_y * 0.8);
		//use the scaling factor to adjust the size of the rectangle
		m_winRect.right = m_winRect.left + (BUTTON_WIDTH * m_scaling.width);
		m_winRect.bottom = m_winRect.top + (BUTTON_HEIGHT * m_scaling.height);
		//the origin is the same as the rect pos
		m_origin = D2D1::Point2F(m_winRect.left, m_winRect.top);

		this->prepareRectPos();
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
	m_colorBrush->SetTransform(D2D1::Matrix3x2F::Scale(m_TextScaling, m_origin));
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
		m_colorBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Red, 1.0f));
		m_bitmapBrush->SetTransform(D2D1::Matrix3x2F::Translation(D2D1::SizeF(m_Position.x, m_Position.y - 67)) * D2D1::Matrix3x2F::Scale(m_scaling, m_origin));
	}
	else if (PtInRect(&m_winRect, mousePos) && !isPressed)
	{
		m_colorBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black, 1.0f));
		m_bitmapBrush->SetTransform(D2D1::Matrix3x2F::Translation(D2D1::SizeF(m_Position.x, m_Position.y - 131)) * D2D1::Matrix3x2F::Scale(m_scaling, m_origin));
	}
	else
	{
		m_colorBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White, 1.0f));
		m_bitmapBrush->SetTransform(D2D1::Matrix3x2F::Translation(D2D1::SizeF(m_Position.x, m_Position.y - 3)) * D2D1::Matrix3x2F::Scale(m_scaling, m_origin));
	}
	
	return false;
}

void Button::Draw(ID2D1DeviceContext1 * p2DDevCon)
{
	p2DDevCon->BeginDraw();
	p2DDevCon->FillRectangle(&m_rect, m_bitmapBrush.Get());
	p2DDevCon->DrawRectangle(m_rect, m_basicBrush.Get());
	float rectWidth = m_rect.right - m_rect.left;
	p2DDevCon->DrawTextLayout(D2D1::Point2F(m_Position.x + (rectWidth/2) - m_content.length()*6.5, m_Position.y - 13), m_layout.Get(), m_colorBrush.Get());
	if (FAILED(p2DDevCon->EndDraw()))
		throw std::runtime_error("WARNING: Button draw call failed.");
}

void Button::onResize()
{
	RECT windowRes;
	if (::GetWindowRect(m_hwnd, &windowRes))
	{
		//calculate the width and height of the window
		float width = float(windowRes.right - windowRes.left);
		float height = float(windowRes.bottom - windowRes.top);
		float offset_x = width / BUTTON_SCALING_X;
		float offset_y = height / BUTTON_SCALING_Y;
		m_TextScaling = D2D1::SizeF(offset_x, offset_y);
		m_colorBrush->SetTransform(D2D1::Matrix3x2F::Scale(m_TextScaling, m_origin));
		//place the button based on the offset values
		m_winRect.left = windowRes.left + (m_Position.x * offset_x);
		m_winRect.top = windowRes.top + (m_Position.y * offset_y);
		//calculate the scaling
		m_scaling = D2D1::SizeF(offset_x * 0.3, offset_y * 0.8);
		//use the scaling factor to adjust the size of the rectangle
		m_winRect.right = m_winRect.left + (BUTTON_WIDTH * m_scaling.width);
		m_winRect.bottom = m_winRect.top + (BUTTON_HEIGHT * m_scaling.height);
		//the origin is the same as the rect pos
		m_origin = D2D1::Point2F(m_winRect.left, m_winRect.top);
		m_layout->SetMaxWidth(BUTTON_WIDTH * m_scaling.width);
		m_layout->SetMaxHeight(BUTTON_HEIGHT * m_scaling.height);
		this->prepareRectPos();
	}
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

void Button::prepareRectPos()
{
	m_rect.left = m_winRect.left;
	m_rect.right = m_winRect.right;
	m_rect.top = m_winRect.top;
	m_rect.bottom = m_winRect.bottom;
}

