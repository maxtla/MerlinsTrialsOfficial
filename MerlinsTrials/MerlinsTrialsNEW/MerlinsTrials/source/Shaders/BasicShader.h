#pragma once
#ifndef BASIC_SHADER_H
#define BASIC_SHADER_H
#include <DirectXMath.h>
#include <memory>
#include <CommonStates.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <iostream>
#include <wrl\client.h>
#include <vector>
#include <SimpleMath.h>
#include "..\Helpers\Enumerators.h"


class BasicShader
{
private:
	ID3D11Device* gDevice;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout; 	

	void createVertexPositionNormalColorShader();
	void createVertexPositionNormalTextureShader();

public:	
	BasicShader(); 
	~BasicShader();
	std::unique_ptr<DirectX::BasicEffect> m_effect;	
	std::unique_ptr<DirectX::CommonStates> m_states;
	ID3D11DeviceContext* gDeviceContext;

	void init(ID3D11Device* in_gDevice, ID3D11DeviceContext* in_gDeviceContext);
	void createShader(SHADERTYPE whatShader);
	
	//functions that set up the shader states
	void setBlendState(BLENDSTATES state = OPAQUE_STATE, DirectX::SimpleMath::Vector4 blendFactor = DirectX::SimpleMath::Vector4(0.f, 0.f, 0.f, 1.f), UINT SampleMask = 0xFFFFFFFF);
	void setDepthStencilState(DEPTHSTENCILSTATES state = DEPTH_DEFAULT_STATE, UINT stencilRef = 0u);
	void setRasterizerState(RASTERIZERSTATES state = CULL_COUNTERCLOCKWISE_STATE);
	void setSamplerState(SAMPLERSTATES state = LINEAR_WRAP_STATE);
	
	void Apply() 
	{ 
		gDeviceContext->IASetInputLayout(this->m_inputLayout.Get());
		m_effect->Apply(gDeviceContext); 
	}

	ID3D11InputLayout * getInputLayout() { return this->m_inputLayout.Get(); }
};

#endif
