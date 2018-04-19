#include "ModelBase.h"

ModelBase::ModelBase()
{
	this->device = nullptr;
	this->geometry = nullptr;
	this->wMatrix = DirectX::XMMatrixIdentity();
}

ModelBase::ModelBase(ID3D11Device * in_device)
{
	this->device = in_device;
	this->geometry = nullptr;
	this->wMatrix = DirectX::XMMatrixIdentity();
}

ModelBase::ModelBase(ID3D11Device *in_device, const Geometry* in_geometry)
{
	this->device = in_device;
	this->geometry = in_geometry;
	this->wMatrix = DirectX::XMMatrixIdentity();
}

ModelBase::ModelBase(ID3D11Device *in_device, const DirectX::XMMATRIX &in_wMatrix, const Geometry* in_Geometry)
{
	this->geometry = in_Geometry;
	this->wMatrix = in_wMatrix;
	this->device = in_device;
}

ModelBase::~ModelBase()
{
}

void ModelBase::setWorldMatrix(const DirectX::XMMATRIX & in_wMatrix)
{
	this->wMatrix = in_wMatrix;
}

void ModelBase::setGeometry(const Geometry * in_geometry)
{
	this->geometry = in_geometry;
}

const Geometry * ModelBase::getGeometry() const
{
	return this->geometry;
}


bool ModelBase::createBuffers() {

	//Create Vertex Buffer
	HRESULT hr;
	D3D11_BUFFER_DESC vBufferDesc;
	ZeroMemory(&vBufferDesc, sizeof(vBufferDesc));

	//Flags
	vBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vBufferDesc.ByteWidth = sizeof(Geometry::Vertex) * this->geometry->getVertexCount();
	vBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vBufferDesc.CPUAccessFlags = 0;
	vBufferDesc.MiscFlags = 0;

	//Data
	D3D11_SUBRESOURCE_DATA vBufferData;
	ZeroMemory(&vBufferData, sizeof(vBufferData));

	vBufferData.pSysMem = this->geometry->vertices.data();
	hr = device->CreateBuffer(&vBufferDesc, &vBufferData, &this->vBuffer);
	if (FAILED(hr))
	{
		return false;
	}
	//Create index buffer
	D3D11_BUFFER_DESC iBufferDesc;
	ZeroMemory(&iBufferDesc, sizeof(iBufferDesc));

	//Flags
	iBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	iBufferDesc.ByteWidth = sizeof(int) * (this->geometry->getFaceCount() * 3);
	iBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	iBufferDesc.CPUAccessFlags = 0;
	iBufferDesc.MiscFlags = 0;

	//Data
	D3D11_SUBRESOURCE_DATA iBufferData;
	ZeroMemory(&iBufferData, sizeof(iBufferData));

	iBufferData.pSysMem = this->geometry->indices.data();
	hr = device->CreateBuffer(&iBufferDesc, &iBufferData, &this->iBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	//end
	return true;
}

ID3D11Buffer* ModelBase::getVBuffer() const
{

	return this->vBuffer;

}

ID3D11Buffer* ModelBase::getIBuffer() const
{

	return this->iBuffer;

}