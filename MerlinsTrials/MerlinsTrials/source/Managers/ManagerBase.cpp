#include "stdafx.h"
#include "ManagerBase.h"


ManagerBase::ManagerBase()
{
	this->cb = nullptr;
	this->player = nullptr;
	this->device = nullptr;
	this->deviceContext = nullptr;
}

ManagerBase::ManagerBase(Player* in_player, ID3D11Device* in_device, ID3D11DeviceContext * in_context)
{
	this->player = in_player;
	this->device = in_device;
	this->deviceContext = in_context;

	this->createCB();
}

ManagerBase::~ManagerBase()
{
}

void ManagerBase::createCB()
{
	//to use if needed
	HRESULT hr;

	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(Matrices);
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &this->matrices;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	hr = this->device->CreateBuffer(&cbDesc, &InitData, &this->cb);
	if (FAILED(hr))
	{
		exit(-1);
	}
}

void ManagerBase::rebindCB()
{
	//to use if needed
}
