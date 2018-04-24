#include "stdafx.h"
#include "Direct3DEngine.h"


Direct3DEngine::Direct3DEngine()
{
	
}


Direct3DEngine::~Direct3DEngine()
{
	pDev.Reset();
	pDevCon.Reset();
	m_pSwapChain.Reset();
	m_pRTV.Reset();
	m_pBackBuffer.Reset();
	m_pDSV.Reset();
	m_pDB.Reset();
	m_pDSS.Reset();
	m_pRS.Reset();
}

bool Direct3DEngine::initialize(HWND hwnd)
{
	if (!initDeviceAndSwapChain(hwnd))
		return false;
	if (!initRenderTargetView())
		return false;
	if (!initDepthStencilView(hwnd))
		return false;
	if (!initDepthStencilState())
		return false;
	if (!initRasterizerState())
		return false;

	return true;
}

void Direct3DEngine::resetEngine()
{
	//clear backbuffer and depth buffer
	//this->pDevCon->ClearState();
	float color[4] = { 0.f, 0.f, 0.f, 1.0f };

	this->pDevCon->ClearRenderTargetView(this->m_pRTV.Get(), color);
	this->pDevCon->ClearDepthStencilView(this->m_pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

	//prepare render target view and dsv state
	this->pDevCon->OMSetRenderTargets(1, this->m_pRTV.GetAddressOf(), this->m_pDSV.Get());
	this->pDevCon->OMSetDepthStencilState(this->m_pDSS.Get(), 1);

	//prepare rasterizer
	this->pDevCon->RSSetState(this->m_pRS.Get());
	this->pDevCon->RSSetViewports(1, &this->m_viewPort);
}


void Direct3DEngine::PresentFrame()
{
	//this function should be specified by Global Video Settings
	//ex. if VSync is enabled we set a flag to allow screen tearing
	//current setting: do not wait and present as fast as possible
	this->m_pSwapChain->Present(0, DXGI_PRESENT_DO_NOT_WAIT);
}

void Direct3DEngine::setViewport(D3D11_VIEWPORT vp)
{
	this->m_viewPort = vp;
}

void Direct3DEngine::setDepthStencilState(ID3D11DepthStencilState * pDSS)
{
	if (this->m_pDSS)
		this->m_pDSS.Reset();

	this->m_pDSS = nullptr;
	this->m_pDSS = pDSS;
}

void Direct3DEngine::setRasterizerState(ID3D11RasterizerState * pRS)
{
	if (this->m_pRS)
		this->m_pRS.Reset();

	m_pRS = nullptr;
	m_pRS = pRS;
}

bool Direct3DEngine::setFullscreenState(bool fullscreen)
{
	HRESULT hr;
	hr = this->m_pSwapChain->SetFullscreenState(fullscreen, NULL);
	if (FAILED(hr))
		return false;
	return true;
}

bool Direct3DEngine::resize(HWND hwnd)
{
	HRESULT hr;
	DXGI_SWAP_CHAIN_DESC scDesc;
	DXGI_MODE_DESC dxDesc;

	hr = this->m_pSwapChain->GetDesc(&scDesc);
	if (FAILED(hr))
		return false;

	dxDesc = scDesc.BufferDesc;

	RECT rect;
	ZeroMemory(&rect, sizeof(RECT));

	if (GetWindowRect(hwnd, &rect))
	{
		dxDesc.Width = rect.right - rect.left;
		dxDesc.Height = rect.bottom - rect.top;

		hr = this->m_pSwapChain->ResizeTarget(&dxDesc);
		if (FAILED(hr))
			return false;

		hr = this->m_pSwapChain->ResizeBuffers(
			0,
			dxDesc.Width,
			dxDesc.Height,
			dxDesc.Format,
			NULL);
		if (FAILED(hr))
			return false;
	}
	else
		return false;

	return true;
}

bool Direct3DEngine::setRefreshRate(unsigned int hertz)
{
	HRESULT hr;
	DXGI_SWAP_CHAIN_DESC scDesc;
	DXGI_MODE_DESC dxDesc;

	hr = this->m_pSwapChain->GetDesc(&scDesc);
	if (FAILED(hr))
		return false;

	dxDesc = scDesc.BufferDesc;

	dxDesc.RefreshRate.Denominator = hertz;

	hr = this->m_pSwapChain->ResizeTarget(&dxDesc);
	if (FAILED(hr))
		return false;

	hr = this->m_pSwapChain->ResizeBuffers(
		0,
		dxDesc.Width,
		dxDesc.Height,
		dxDesc.Format,
		NULL);
	
	if (FAILED(hr))
		return false;

	return true;
}


bool Direct3DEngine::initDeviceAndSwapChain(HWND hwnd)
{
	HRESULT hr;
	//buffer description
	DXGI_MODE_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

	//swapchain description
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	/*rect to retrieve the windows width and height*/
	RECT rect;
	ZeroMemory(&rect, sizeof(RECT));

	if (GetWindowRect(hwnd, &rect))
	{
		bufferDesc.Width = rect.right - rect.left;
		bufferDesc.Height = rect.bottom - rect.top;
		bufferDesc.RefreshRate.Numerator = 60;
		bufferDesc.RefreshRate.Denominator = 1;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		swapChainDesc.BufferDesc = bufferDesc;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = hwnd;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		D3D_FEATURE_LEVEL FeatureLevels[] = {
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		hr = D3D11CreateDeviceAndSwapChain(
			NULL, 
			D3D_DRIVER_TYPE_HARDWARE,
			NULL, 
			D3D11_CREATE_DEVICE_BGRA_SUPPORT,
			FeatureLevels,
			ARRAYSIZE(FeatureLevels),
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&m_pSwapChain,
			&pDev,
			NULL,
			&pDevCon);

		if (FAILED(hr))
			return false;

		//now retrieve the backbuffer from the created swapchain so we can create the render target view
		hr = m_pSwapChain.Get()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&this->m_pBackBuffer);
		if (FAILED(hr))
			return false;
	}
	else
		return false;

	return true;
}

bool Direct3DEngine::initRenderTargetView()
{
	HRESULT hr;
	//we can specify the description but for now thats of no concern so we use NULL
	hr = pDev->CreateRenderTargetView(this->m_pBackBuffer.Get(), NULL, &this->m_pRTV);
	if (FAILED(hr))
		return false;

	return true;
}

bool Direct3DEngine::initDepthStencilView(HWND hwnd)
{
	HRESULT hr;
	//first we need to specify and create the depth buffer
	D3D11_TEXTURE2D_DESC dpDesc;
	ZeroMemory(&dpDesc, sizeof(D3D11_TEXTURE2D_DESC));
	//then we can create the DSV
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	//rect to retrieve the windows width and height
	RECT rect;
	ZeroMemory(&rect, sizeof(RECT));

	if (GetWindowRect(hwnd, &rect))
	{
		dpDesc.Width = rect.right - rect.left;
		dpDesc.Height = rect.bottom - rect.top;
		dpDesc.MipLevels = 1;
		dpDesc.ArraySize = 1;
		dpDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dpDesc.SampleDesc.Count = 1;
		dpDesc.SampleDesc.Quality = 0;
		dpDesc.Usage = D3D11_USAGE_DEFAULT;
		dpDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		dpDesc.CPUAccessFlags = 0;
		dpDesc.MiscFlags = 0;

		//create the depth buffer
		hr = pDev->CreateTexture2D(&dpDesc, NULL, &this->m_pDB);
		if (FAILED(hr))
			return false;

		dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;

		hr = pDev->CreateDepthStencilView(this->m_pDB.Get(), &dsvDesc, &this->m_pDSV);
		if (FAILED(hr))
			return false;
	}
	else
		return false;

	return true;
}

bool Direct3DEngine::initDepthStencilState()
{
	HRESULT hr;
	D3D11_DEPTH_STENCIL_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
	dsDesc.StencilEnable = FALSE;
	dsDesc.StencilReadMask = 0xFF;
	dsDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	hr = pDev->CreateDepthStencilState(&dsDesc, &this->m_pDSS);
	if (FAILED(hr))
		return false;

	return true;
}

bool Direct3DEngine::initRasterizerState()
{
	HRESULT hr;
	D3D11_RASTERIZER_DESC rsDesc;
	ZeroMemory(&rsDesc, sizeof(D3D11_RASTERIZER_DESC));

	rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK; //backface culling
	rsDesc.FrontCounterClockwise = FALSE; //clockwise rendering
	rsDesc.DepthBias = 0; //no need for this yet
	rsDesc.DepthBiasClamp = 0.0f;
	rsDesc.DepthClipEnable = TRUE;
	rsDesc.ScissorEnable = FALSE;
	rsDesc.MultisampleEnable = FALSE;
	rsDesc.AntialiasedLineEnable = TRUE;

	hr = pDev->CreateRasterizerState(&rsDesc, &this->m_pRS);
	if (FAILED(hr))
		return false;

	return true;
}


