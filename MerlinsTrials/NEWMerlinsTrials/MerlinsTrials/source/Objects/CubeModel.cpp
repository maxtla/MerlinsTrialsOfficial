#include "stdafx.h"
#include "CubeModel.h"
#include "CubeModel.h"


CubeModel::CubeModel(DirectX::XMMATRIX wMatrix, bool isSolid, bool isVisible, int in_id)
{
	this->wMatrix = wMatrix;
	this->id = in_id;
	this->isSolid = isSolid;
	this->isVisible = isVisible;
}

CubeModel::~CubeModel()
{

}

void CubeModel::loadModel(const std::string &path, ID3D11Device* device, ID3D11DeviceContext* context)
{
	std::vector<Mesh*> meshi;
	importer.importFBXModel(path, meshi, device, context, BOUNDINGTYPE::AABB);
	this->mesh = meshi[0];
}

void CubeModel::setNormalMapShader(NormalMapShader * in_shader)
{
	this->m_NormalMapShader = in_shader;
}

void CubeModel::setBasicShader(BasicShader * in_shader)
{
	this->m_BasicShader = in_shader;
}

void CubeModel::setVisisble(const bool & in_value)
{
	this->isVisible = in_value;
}

void CubeModel::setSolid(const bool & in_value)
{
	this->isSolid = in_value;
}

void CubeModel::setWorld(const XMMATRIX & in_matrix)
{
	this->wMatrix = in_matrix;
}

DirectX::BoundingBox CubeModel::getBoundingBox()
{
	return this->mesh->m_AABB;
}

float CubeModel::getGrabDistance() const
{
	return this->grabDistance;
}

int CubeModel::getID() const
{
	return this->id;
}

bool CubeModel::getVisisble() const
{
	return this->isVisible;
}

bool CubeModel::getSolid() const
{
	return this->isSolid;
}

XMMATRIX CubeModel::getWorld() const
{
	return this->wMatrix;
}

void CubeModel::update()
{

}

void CubeModel::Draw(ID3D11DeviceContext * in_context, Matrix view, Matrix proj)
{

	this->mesh->Draw(this->m_BasicShader);
}
