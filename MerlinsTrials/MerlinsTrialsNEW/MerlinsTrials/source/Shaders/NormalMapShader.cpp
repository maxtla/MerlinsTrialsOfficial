#include "stdafx.h"
#include "NormalMapShader.h"


NormalMapShader::NormalMapShader()
{

}

NormalMapShader::~NormalMapShader()
{

}

void NormalMapShader::createWithColorEnabled()
{
	//In normal map effects, normals and textures are enabled by default
	//We dont make use of fog yet so its disabled by default
	this->m_effect->SetFogEnabled(false);
	this->m_effect->SetVertexColorEnabled(true);

	this->m_effect->EnableDefaultLighting();


	void const* shaderByteCode;
	size_t byteCodeLength;

	this->m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	HRESULT hr = 0;

	hr = this->gDevice->CreateInputLayout(DirectX::VertexPositionNormalColorTexture::InputElements, DirectX::VertexPositionNormalColorTexture::InputElementCount,
		shaderByteCode, byteCodeLength, m_inputLayout.ReleaseAndGetAddressOf());

	if (FAILED(hr))
	{
		throw std::runtime_error("ERROR: Could not create input layout for VertexPositionColor shader.");
	}
}

void NormalMapShader::createWithColorDisabled()
{
	//In normal map effects, normals and textures are enabled by default
	//We dont make use of fog yet so its disabled by default
	this->m_effect->SetFogEnabled(false);
	this->m_effect->SetVertexColorEnabled(false);

	this->m_effect->EnableDefaultLighting();

	void const* shaderByteCode;
	size_t byteCodeLength;

	this->m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	HRESULT hr = 0;

	hr = this->gDevice->CreateInputLayout(DirectX::VertexPositionNormalTexture::InputElements, DirectX::VertexPositionNormalTexture::InputElementCount,
		shaderByteCode, byteCodeLength, m_inputLayout.ReleaseAndGetAddressOf());

	if (FAILED(hr))
	{
		throw std::runtime_error("ERROR: Could not create input layout for VertexPostionNormalTexture shader.");
	}
}

void NormalMapShader::init(ID3D11Device* in_gDevice, ID3D11DeviceContext* in_gDeviceContext) {

	this->gDevice = in_gDevice;
	this->gDeviceContext = in_gDeviceContext;
	this->m_effect = std::make_unique<DirectX::NormalMapEffect>(this->gDevice);
	this->m_states = std::make_unique<DirectX::CommonStates>(this->gDevice);
}

void NormalMapShader::createShader(NORMALMAP_SHADER_TYPE whatShader)
{
	switch (whatShader)
	{
	case NO_COLOR:
		try
		{
			this->createWithColorDisabled();
		}
		catch (std::exception& e)
		{
			std::string exc = e.what();
			OutputDebugString(std::wstring(exc.begin(), exc.end()).c_str());
		}
		break;

	case WITH_COLOR:
		try
		{
			this->createWithColorEnabled();
		}
		catch (std::exception& e)
		{
			std::string exc = e.what();
			OutputDebugString(std::wstring(exc.begin(), exc.end()).c_str());
		}
		break;
	default:
		throw std::runtime_error("ERROR: Unable to create shader.\n");
	}
}

void NormalMapShader::setBlendState(BLENDSTATES state, DirectX::SimpleMath::Vector4 blendFactor, UINT SampleMask)
{
	float _blendFactor[4] = { blendFactor.x, blendFactor.y, blendFactor.z, blendFactor.w };
	switch (state)
	{
	case OPAQUE_STATE:
		this->gDeviceContext->OMSetBlendState(m_states->Opaque(), _blendFactor, SampleMask);
		break;
	case ALPHPA_BLEND_STATE:
		this->gDeviceContext->OMSetBlendState(m_states->AlphaBlend(), _blendFactor, SampleMask);
		break;
	case ADDITIVE_STATE:
		this->gDeviceContext->OMSetBlendState(m_states->Additive(), _blendFactor, SampleMask);
		break;
	case NON_PREMULTIPLIED_STATE:
		this->gDeviceContext->OMSetBlendState(m_states->NonPremultiplied(), _blendFactor, SampleMask);
		break;
	default:
		break;
	}
}

void NormalMapShader::setDepthStencilState(DEPTHSTENCILSTATES state, UINT stencilRef)
{
	switch (state)
	{
	case DEPTH_NONE_STATE:
		this->gDeviceContext->OMSetDepthStencilState(m_states->DepthNone(), stencilRef);
		break;
	case DEPTH_DEFAULT_STATE:
		this->gDeviceContext->OMSetDepthStencilState(m_states->DepthDefault(), stencilRef);
		break;
	case DEPTH_READ_STATE:
		this->gDeviceContext->OMSetDepthStencilState(m_states->DepthRead(), stencilRef);
		break;
	default:
		break;
	}
}

void NormalMapShader::setRasterizerState(RASTERIZERSTATES state)
{
	switch (state)
	{
	case CULL_NONE_STATE:
		this->gDeviceContext->RSSetState(m_states->CullNone());
		break;
	case CULL_CLOCKWISE_STATE:
		this->gDeviceContext->RSSetState(m_states->CullClockwise());
		break;
	case CULL_COUNTERCLOCKWISE_STATE:
		this->gDeviceContext->RSSetState(m_states->CullCounterClockwise());
		break;
	case WIREFRAME_STATE:
		this->gDeviceContext->RSSetState(m_states->Wireframe());
		break;
	}
}

void NormalMapShader::setSamplerState(SAMPLERSTATES state)
{
	//i'm not sure ther is another way than this.. bad memory usage :(
	auto pointWrapSamplerState = m_states->PointWrap();
	auto pointClampSamplerState = m_states->PointClamp();
	auto linearWrapSamplerState = m_states->LinearWrap();
	auto linearClampSamplerState = m_states->LinearClamp();
	auto anisotropicWrapSamplerState = m_states->AnisotropicWrap();
	auto anisotropicClampSamplerState = m_states->AnisotropicClamp();

	switch (state)
	{
	case POINT_WRAP_STATE:
		this->gDeviceContext->PSSetSamplers(0, 1, &pointWrapSamplerState);
		break;
	case POINT_CLAMP_STATE:
		this->gDeviceContext->PSSetSamplers(0, 1, &pointClampSamplerState);
		break;
	case LINEAR_WRAP_STATE:
		this->gDeviceContext->PSSetSamplers(0, 1, &linearWrapSamplerState);
		break;
	case LINEAR_CLAMP_STATE:
		this->gDeviceContext->PSSetSamplers(0, 1, &linearClampSamplerState);
		break;
	case ANISOTROPIC_WRAP_STATE:
		this->gDeviceContext->PSSetSamplers(0, 1, &anisotropicWrapSamplerState);
		break;
	case ANISOTROPIC_CLAMP_STATE:
		this->gDeviceContext->PSSetSamplers(0, 1, &anisotropicClampSamplerState);
		break;
	default:
		break;
	}
}