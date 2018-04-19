#ifndef SHADERS_H
#define SHADERS_h
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
class Shaders
{
private:
	enum SHADER { Basic, Glowing }; //Till exempel
	ID3D11Device* gDevice;
	ID3D11DeviceContext* gDeviceContext;

	DirectX::XMMATRIX wMatrix;	
	DirectX::XMMATRIX proj;
	DirectX::XMMATRIX view;
	DirectX::SimpleMath::Vector3 specColor;
	DirectX::SimpleMath::Vector3 diffuseColor;
	DirectX::XMVECTOR camPos;

	float specExponent;
	float opacity;

	DirectX::XMVECTOR lightDirection;
	DirectX::XMVECTOR lightDiffuseColor;
	DirectX::XMVECTOR lightSpecularColor;

	std::unique_ptr<DirectX::BasicEffect> m_effect;	
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout; //Eller en egen input layout	

	ID3D11Buffer* vBuffer;
	ID3D11Buffer* iBuffer;

	void createBasicShader();

public:	
	Shaders(ID3D11Device* in_gDevice, ID3D11DeviceContext* in_gDeviceContext); //Inkluderar 
	~Shaders();

	void createShader(SHADER whatShader);
	void setShaderParams(DirectX::XMMATRIX in_WMatrix, DirectX::SimpleMath::Vector3 in_SpecColor, DirectX::SimpleMath::Vector3 in_DiffuseColor,
		DirectX::SimpleMath::Vector3 in_Emissive, float in_SpecExponent, float in_Opacity);
	void setCameraParams(DirectX::XMMATRIX in_Proj, DirectX::XMMATRIX in_View);
	void setShaderLightParams(DirectX::SimpleMath::Vector3 in_Ambient, DirectX::XMVECTOR in_IightDirection[DirectX::IEffectLights::MaxDirectionalLights], DirectX::XMVECTOR in_LightDiffuseColor[DirectX::IEffectLights::MaxDirectionalLights],
		DirectX::XMVECTOR in_LightSpecularColor[DirectX::IEffectLights::MaxDirectionalLights]);
	void setShaderFogParams(DirectX::XMVECTOR in_FogColor, DirectX::XMVECTOR fogVector);
	void setTexture(Texture in_Tex);


};

#endif
