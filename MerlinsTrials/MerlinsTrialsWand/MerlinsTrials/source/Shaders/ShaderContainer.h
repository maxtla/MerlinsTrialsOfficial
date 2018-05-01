#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <d3d11.h>
#include <d3dcompiler.h>
#include <fstream>

enum ShaderType {
	Vertex,
	Hull,
	Domain,
	Geometry,
	Pixel
};

using namespace std;

class ShaderContainer
{
public:
	ShaderContainer();
	~ShaderContainer();
	bool loadShader(int shaderType, ID3D11Device * pDev, HWND hwnd, WCHAR *filePath, CHAR *entryPoint);
	bool createInputLayout(ID3D11Device* pDev, D3D11_INPUT_ELEMENT_DESC *layoutDescriptions, unsigned int numOfElements);
	void Release();
	//get functions
	ID3D11VertexShader* getVertexShader() const;
	ID3D11HullShader*	getHullShader() const;
	ID3D11DomainShader*	getDomainShader() const;
	ID3D11GeometryShader*	getGeometryShader() const;
	ID3D11PixelShader*	getPixelShader() const;
	ID3D11InputLayout* getInputLayout() const;

private:
	//shader members
	ID3D11VertexShader* pVertexShader;
	ID3D11HullShader*	pHullShader;
	ID3D11DomainShader*	pDomainShader;
	ID3D11GeometryShader*	pGeometryShader;
	ID3D11PixelShader*	pPixelShader;
	//shader related members
	ID3D11InputLayout* pInputLayout;
	//methods
	bool loadVertexShader(ID3D11Device * pDev, HWND hwnd, WCHAR *filePath, CHAR *entryPoint);
	bool loadHullShader(ID3D11Device * pDev, HWND hwnd, WCHAR *filePath, CHAR *entryPoint);
	bool loadDomainShader(ID3D11Device * pDev, HWND hwnd, WCHAR *filePath, CHAR *entryPoint);
	bool loadGeometryShader(ID3D11Device * pDev, HWND hwnd, WCHAR *filePath, CHAR *entryPoint);
	bool loadPixelShader(ID3D11Device * pDev, HWND hwnd, WCHAR *filePath, CHAR *entryPoint);
	HRESULT loadShaderBuffer(ID3D10Blob **shaderBuffer, ID3D10Blob **errorMsg, WCHAR *filePath, CHAR *entryPoint, const char *shaderModel);
	void outputErrorMessage(ID3D10Blob* errorMsg, HWND hwnd, WCHAR *filePath, int shaderType);
	//temporary blob for creation of the input layout
	ID3D10Blob *vertexShaderBuffer;
};

#endif