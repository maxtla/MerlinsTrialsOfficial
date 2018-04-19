#include "Shaders.h"

void Shaders::createBasicShader()
{
	UINT32 vertexSize = sizeof(float) * DirectX::VertexPositionColor::InputElementCount;
	UINT32 offset = 0;
	gDeviceContext->IASetVertexBuffers(0, 1, &this->vBuffer, &vertexSize, &offset);
	gDeviceContext->IASetIndexBuffer(this->iBuffer, DXGI_FORMAT_R32_UINT, offset);

	 //vet inte om det funkar
	
	this->m_effect->SetVertexColorEnabled(true);

	void const* shaderByteCode;
	size_t byteCodeLength;

	this->m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	HRESULT hr = 0;

	hr = this->gDevice->CreateInputLayout(DirectX::VertexPositionColor::InputElements, DirectX::VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength, m_inputLayout.ReleaseAndGetAddressOf());
	
	if (FAILED(hr))
	{
		throw std::runtime_error("ERROR: Could not create input layout for Basic shader.");
	}

	m_effect->Apply(this->gDeviceContext);

	gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	gDeviceContext->IASetInputLayout(m_inputLayout.Get());
	
}

Shaders::Shaders(ID3D11Device* in_gDevice, ID3D11DeviceContext* in_gDeviceContext)
{
	this->gDevice = in_gDevice;
	this->gDeviceContext = in_gDeviceContext;
	this->m_effect = std::make_unique<DirectX::BasicEffect>(this->gDevice);

}

void Shaders::createShader(SHADER whatShader)
{
	switch (whatShader)
	{
	case Basic:
		try
		{
			this->createBasicShader();
		}
		catch (std::exception& e)
		{
			OutputDebugString(e.what());
		}
		

		break;

	}
}

void Shaders::setShaderParams(DirectX::XMMATRIX in_WMatrix, DirectX::SimpleMath::Vector3 in_SpecColor, DirectX::SimpleMath::Vector3 in_DiffuseColor,
	DirectX::SimpleMath::Vector3 in_Emissive, float in_SpecExponent, float in_Opacity)
{
	this->m_effect->SetWorld(in_WMatrix);
	this->m_effect->SetSpecularColor(in_SpecColor);
	this->m_effect->SetDiffuseColor(in_DiffuseColor);	
	this->m_effect->SetEmissiveColor(in_Emissive);
	this->m_effect->SetSpecularPower(in_SpecExponent);
	//Opacity?
}

void Shaders::setCameraParams(DirectX::XMMATRIX in_Proj, DirectX::XMMATRIX in_View)
{
	this->m_effect->SetProjection(in_Proj);
	this->m_effect->SetView(in_View);	
}

void Shaders::setShaderLightParams(DirectX::SimpleMath::Vector3 in_Ambient, DirectX::XMVECTOR in_IightDirection[DirectX::IEffectLights::MaxDirectionalLights], DirectX::XMVECTOR in_LightDiffuseColor[DirectX::IEffectLights::MaxDirectionalLights], DirectX::XMVECTOR in_LightSpecularColor[DirectX::IEffectLights::MaxDirectionalLights])
{

}
