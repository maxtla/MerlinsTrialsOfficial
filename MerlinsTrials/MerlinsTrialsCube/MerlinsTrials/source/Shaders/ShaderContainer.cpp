#include "stdafx.h"
#include "ShaderContainer.h"



ShaderContainer::ShaderContainer()
{
	this->pDomainShader = nullptr;
	this->pGeometryShader = nullptr;
	this->pHullShader = nullptr;
	this->pPixelShader = nullptr;
	this->pVertexShader = nullptr;
	this->pInputLayout = nullptr;
}


ShaderContainer::~ShaderContainer()
{
}

bool ShaderContainer::loadShader(int shaderType, ID3D11Device * pDev, HWND hwnd, WCHAR * filePath, CHAR * entryPoint)
{
	switch (shaderType)
	{
	case ShaderType::Vertex:
		return loadVertexShader(pDev, hwnd, filePath, entryPoint);
		break;
	case ShaderType::Hull:
		return loadHullShader(pDev, hwnd, filePath, entryPoint);
		break;
	case ShaderType::Domain:
		return loadDomainShader(pDev, hwnd, filePath, entryPoint);
		break;
	case ShaderType::Geometry:
		return loadGeometryShader(pDev, hwnd, filePath, entryPoint);
		break;
	case ShaderType::Pixel:
		return loadPixelShader(pDev, hwnd, filePath, entryPoint);
		break;
	default:
		return false;
		break;
	}
}

bool ShaderContainer::createInputLayout(ID3D11Device * pDev, D3D11_INPUT_ELEMENT_DESC * layoutDescriptions, unsigned int numOfElements)
{
	HRESULT hr;
	hr = pDev->CreateInputLayout(layoutDescriptions, numOfElements, this->vertexShaderBuffer->GetBufferPointer(), this->vertexShaderBuffer->GetBufferSize(), &this->pInputLayout);

	this->vertexShaderBuffer->Release();
	this->vertexShaderBuffer = nullptr;

	if (FAILED(hr))
		return false;

	return true;
}

void ShaderContainer::Release()
{
	if (this->pVertexShader)
	{
		this->pVertexShader->Release();
		this->pVertexShader = nullptr;
	}
	if (this->pHullShader)
	{
		this->pHullShader->Release();
		this->pHullShader = nullptr;
	}
	if (this->pDomainShader)
	{
		this->pDomainShader->Release();
		this->pDomainShader = nullptr;
	}
	if (this->pGeometryShader)
	{
		this->pGeometryShader->Release();
		this->pGeometryShader = nullptr;
	}
	if (this->pPixelShader)
	{
		this->pPixelShader->Release();
		this->pPixelShader = nullptr;
	}
	if (this->pInputLayout)
	{
		this->pInputLayout->Release();
		this->pInputLayout = nullptr;
	}
	if (this->vertexShaderBuffer)
	{
		this->vertexShaderBuffer->Release();
		this->vertexShaderBuffer = nullptr;
	}
}

ID3D11VertexShader * ShaderContainer::getVertexShader() const
{
	return this->pVertexShader;
}

ID3D11HullShader * ShaderContainer::getHullShader() const
{
	return this->pHullShader;
}

ID3D11DomainShader * ShaderContainer::getDomainShader() const
{
	return this->pDomainShader;
}

ID3D11GeometryShader * ShaderContainer::getGeometryShader() const
{
	return this->pGeometryShader;
}

ID3D11PixelShader * ShaderContainer::getPixelShader() const
{
	return this->pPixelShader;
}

ID3D11InputLayout * ShaderContainer::getInputLayout() const
{
	return this->pInputLayout;
}

bool ShaderContainer::loadVertexShader(ID3D11Device * pDev, HWND hwnd, WCHAR * filePath, CHAR * entryPoint)
{
	HRESULT hr;
	ID3D10Blob* shaderBuffer = NULL;
	ID3D10Blob* errorMsg = NULL;

	hr = loadShaderBuffer(&shaderBuffer, &errorMsg, filePath, entryPoint, "vs_5_0");

	if (FAILED(hr))
	{
		if (errorMsg)
		{
			this->outputErrorMessage(errorMsg, hwnd, filePath, ShaderType::Vertex);
		}
		return false;
	}

	hr = pDev->CreateVertexShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, &this->pVertexShader);
	if (FAILED(hr))
		return false;

	this->vertexShaderBuffer = shaderBuffer; 
	if (errorMsg)
	{
		errorMsg->Release();
		errorMsg = NULL;
	}

	return true;
}

bool ShaderContainer::loadHullShader(ID3D11Device * pDev, HWND hwnd, WCHAR * filePath, CHAR * entryPoint)
{
	HRESULT hr;
	ID3D10Blob* shaderBuffer = NULL;
	ID3D10Blob* errorMsg = NULL;

	hr = loadShaderBuffer(&shaderBuffer, &errorMsg, filePath, entryPoint, "hs_5_0");

	if (FAILED(hr))
	{
		if (errorMsg)
		{
			this->outputErrorMessage(errorMsg, hwnd, filePath, ShaderType::Hull);
		}
		return false;
	}

	hr = pDev->CreateHullShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, &this->pHullShader);
	if (FAILED(hr))
		return false;

	shaderBuffer->Release();
	shaderBuffer = NULL;
	if (errorMsg)
	{
		errorMsg->Release();
		errorMsg = NULL;
	}

	return true;
}

bool ShaderContainer::loadDomainShader(ID3D11Device * pDev, HWND hwnd, WCHAR * filePath, CHAR * entryPoint)
{
	HRESULT hr;
	ID3D10Blob* shaderBuffer = NULL;
	ID3D10Blob* errorMsg = NULL;

	hr = loadShaderBuffer(&shaderBuffer, &errorMsg, filePath, entryPoint, "ds_5_0");

	if (FAILED(hr))
	{
		if (errorMsg)
		{
			this->outputErrorMessage(errorMsg, hwnd, filePath, ShaderType::Domain);
		}
		return false;
	}

	hr = pDev->CreateDomainShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, &this->pDomainShader);
	if (FAILED(hr))
		return false;

	shaderBuffer->Release();
	shaderBuffer = NULL;
	if (errorMsg)
	{
		errorMsg->Release();
		errorMsg = NULL;
	}

	return true;
}

bool ShaderContainer::loadGeometryShader(ID3D11Device * pDev, HWND hwnd, WCHAR * filePath, CHAR * entryPoint)
{
	HRESULT hr;
	ID3D10Blob* shaderBuffer = NULL;
	ID3D10Blob* errorMsg = NULL;

	hr = loadShaderBuffer(&shaderBuffer, &errorMsg, filePath, entryPoint, "gs_5_0");

	if (FAILED(hr))
	{
		if (errorMsg)
		{
			this->outputErrorMessage(errorMsg, hwnd, filePath, ShaderType::Geometry);
		}
		return false;
	}

	hr = pDev->CreateGeometryShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, &this->pGeometryShader);
	if (FAILED(hr))
		return false;

	shaderBuffer->Release();
	shaderBuffer = NULL;
	if (errorMsg)
	{
		errorMsg->Release();
		errorMsg = NULL;
	}

	return true;
}

bool ShaderContainer::loadPixelShader(ID3D11Device * pDev, HWND hwnd, WCHAR * filePath, CHAR * entryPoint)
{
	HRESULT hr;
	ID3D10Blob* shaderBuffer = NULL;
	ID3D10Blob* errorMsg = NULL;

	hr = loadShaderBuffer(&shaderBuffer, &errorMsg, filePath, entryPoint, "ps_5_0");

	if (FAILED(hr))
	{
		if (errorMsg)
		{
			this->outputErrorMessage(errorMsg, hwnd, filePath, ShaderType::Pixel);
		}
		return false;
	}

	hr = pDev->CreatePixelShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, &this->pPixelShader);
	if (FAILED(hr))
		return false;

	shaderBuffer->Release();
	shaderBuffer = NULL;
	if (errorMsg)
	{
		errorMsg->Release();
		errorMsg = NULL;
	}

	return true;
}

HRESULT ShaderContainer::loadShaderBuffer(ID3D10Blob ** shaderBuffer, ID3D10Blob ** errorMsg, WCHAR * filePath, CHAR * entryPoint, const char * shaderModel)
{
	return D3DCompileFromFile(filePath,
		nullptr,
		nullptr,
		entryPoint,
		shaderModel,
		D3D10_SHADER_ENABLE_STRICTNESS,
		0,
		shaderBuffer,
		errorMsg);
}

void ShaderContainer::outputErrorMessage(ID3D10Blob * errorMsg, HWND hwnd, WCHAR * filePath, int shaderType)
{
	std::string fileName;
	switch (shaderType)
	{
	case ShaderType::Vertex:
		fileName = "VertexShaderError.txt";
		break;
	case ShaderType::Hull:
		fileName = "HullShaderError.txt";
		break;
	case ShaderType::Domain:
		fileName = "DomainShaderError.txt";
		break;
	case ShaderType::Geometry:
		fileName = "GeometryShaderError.txt";
		break;
	case ShaderType::Pixel:
		fileName = "PixelShaderError.txt";
		break;
	default:
		fileName = "UnknownShaderError.txt";
		break;
	}

	char* compileError;
	unsigned int bufferSize;
	ofstream fOut;

	//pointer to the error message text buffer
	compileError = (char*)(errorMsg->GetBufferPointer());
	//get message size
	bufferSize = (unsigned int)errorMsg->GetBufferSize();
	//open an error text file and write to it
	fOut.open(fileName);
	for (unsigned int i = 0; i < bufferSize; i++)
	{
		fOut << compileError[i];
	}

	fOut.close();

	errorMsg->Release();
	errorMsg = NULL;

	MessageBox(hwnd, L"Error compiling shader.  Check error text file", filePath, MB_OK);
	return;
}
