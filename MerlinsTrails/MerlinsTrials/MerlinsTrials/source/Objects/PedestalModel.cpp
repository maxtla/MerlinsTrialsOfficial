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

#ifndef NDEBUG
	m_batch = std::make_unique<PrimitiveBatch<DirectX::VertexPositionColor>>(m_BasicShader->gDeviceContext);
	this->pDebugShader = new BasicShader(this->m_BasicShader->gDevice, this->m_BasicShader->gDeviceContext, SHADERTYPE::VertexPosCol);
	
	//this->pDebugShader = new BasicShader();
	//this->pDebugShader->init(m_BasicShader->gDevice, m_BasicShader->gDeviceContext);
	//this->pDebugShader->createShader(VertexPosCol);
#endif

}

void PedestalModel::loadModel(const std::string & path, ID3D11Device * device, ID3D11DeviceContext * context)
{
	std::vector<Mesh*> meshi;
	importer.importFBXModel(path, meshi, device, context);
	meshi[0]->hasNoBoundingShape = false;
	meshi[0]->createBoundingShapeFromType(BOUNDINGTYPE::OBB);
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

DirectX::BoundingOrientedBox PedestalModel::getBoundingBox()
{
	return this->mesh->m_OBB;
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

float PedestalModel::getGrabDistance() const
{
	return this->grabDistance;
}

void PedestalModel::update()
{

}

void PedestalModel::Draw(ID3D11DeviceContext * in_context, Matrix view, Matrix proj)
{

	this->m_BasicShader->m_effect->SetMatrices(this->wMatrix, view, proj);
	this->mesh->Draw(this->m_BasicShader);

//#ifndef NDEBUG
//	this->mesh->DrawDebugMode(this->pDebugShader, this->m_batch.get(), view, proj, Vector4(1.f, 0.f, 0.f, 1.f));
//#endif


}
