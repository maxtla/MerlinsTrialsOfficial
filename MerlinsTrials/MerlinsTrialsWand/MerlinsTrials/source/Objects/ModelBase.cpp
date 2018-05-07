#include "stdafx.h"
#include "ModelBase.h"



ModelBase::~ModelBase()
{
}

void ModelBase::setWorldMatrix(const DirectX::XMMATRIX & in_wMatrix)
{
	this->wMatrix = in_wMatrix;
}

void ModelBase::setMeshes(std::vector<Mesh*> meshes)
{
	this->m_Meshes = meshes;

	//DirectX::BoundingOrientedBox box;
	//box = m_Meshes[0]->m_OBB;
	//XMStoreFloat3(&box.Center, XMVector3Transform(XMLoadFloat3(&box.Center), this->wMatrix));
	//m_Meshes[0]->m_OBB = box;

}

void ModelBase::setMeshes(Mesh * c_Mesh)
{
	this->m_Meshes.push_back(c_Mesh);
}

void ModelBase::createBoundongOrientBox()
{

	
}


DirectX::XMMATRIX ModelBase::getWorld() const
{
	return this->wMatrix;
}

