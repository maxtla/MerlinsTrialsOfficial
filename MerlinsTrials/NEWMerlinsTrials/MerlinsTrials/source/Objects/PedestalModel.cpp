#include "stdafx.h"
#include "PedestalModel.h"

PedestalModel::PedestalModel(DirectX::XMMATRIX wMatrix, bool isSolid, bool isVisible, int in_id)
{
	this->wMatrix = wMatrix;
	this->isSolid = isSolid;
	this->isVisible = isVisible;
	this->id = in_id;
}

PedestalModel::~PedestalModel()
{
}

void PedestalModel::setBasicShader(BasicShader* in_shader)
{
	this->m_BasicShader = in_shader;
}

void PedestalModel::loadModel(const std::string & path, ID3D11Device * device, ID3D11DeviceContext * context)
{
	std::vector<Mesh*> meshi;
	importer.importFBXModel(path, meshi, device, context, BOUNDINGTYPE::AABB);
	this->mesh = meshi[0];
}

void PedestalModel::setVisisble(const bool & in_value)
{
	this->isVisible = in_value;
}

void PedestalModel::setSolid(const bool & in_value)
{
	this->isSolid = in_value;
}

void PedestalModel::setWorld(const XMMATRIX & in_matrix)
{
	this->wMatrix = in_matrix;
}

void PedestalModel::setNormalMapShader(NormalMapShader * in_shader)
{
	this->m_NormalMapShader = in_shader;
}

DirectX::BoundingBox PedestalModel::getBoundingBox()
{
	return this->mesh->m_AABB;
}

int PedestalModel::getID() const
{
	return this->id;
}

bool PedestalModel::getVisisble() const
{
	return this->isVisible;
}

bool PedestalModel::getSolid() const
{
	return this->isSolid;
}

XMMATRIX PedestalModel::getWorld() const
{
	return this->wMatrix;
}

void PedestalModel::update()
{

}

void PedestalModel::Draw(ID3D11DeviceContext * in_context, Matrix view, Matrix proj)
{
	this->mesh->Draw(this->m_BasicShader);
}
