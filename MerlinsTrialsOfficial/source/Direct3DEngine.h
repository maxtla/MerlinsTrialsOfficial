#pragma once
#ifndef DIRECT_3D_ENGINE_H
#define DIRECT_3D_ENGINE_H
#include <d3d11.h>

#include <wrl\client.h>

class Direct3DEngine
{
public:
	Direct3DEngine();
	~Direct3DEngine();
	//PUBLIC MEMBERS
	//public core components
	Microsoft::WRL::ComPtr<ID3D11Device> pDev;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDevCon;
	//PUBLIC METHODS
	bool initialize(HWND);
	void resetEngine();
	void Release();
	void PresentFrame();
	//functions to re-specify some base states if we ever have to
	void setViewport(D3D11_VIEWPORT);
	void setDepthStencilState(ID3D11DepthStencilState*);
	void setRasterizerState(ID3D11RasterizerState*);
	bool setFullscreenState(bool);
	bool resize(HWND);
	bool setRefreshRate(unsigned int);
	
	IDXGISwapChain* m_pSwapChain;
protected:
	//PRIVATE MEMBERS
	//private core components
	//private base components
	ID3D11RenderTargetView * m_pRTV;
	ID3D11Texture2D * m_pBackBuffer; //backbuffer
	ID3D11DepthStencilView * m_pDSV;
	ID3D11Texture2D * m_pDB; //depth buffer
	//private state components (basically stuff that sets up depth state, raster state and merger state)
	D3D11_VIEWPORT m_viewPort;
	ID3D11DepthStencilState * m_pDSS;
	ID3D11RasterizerState * m_pRS; //raster state

	//PRIVATE METHODS
	bool initDeviceAndSwapChain(HWND);
	bool initRenderTargetView();
	bool initDepthStencilView(HWND);
	bool initDepthStencilState();
	bool initRasterizerState();
};

#endif