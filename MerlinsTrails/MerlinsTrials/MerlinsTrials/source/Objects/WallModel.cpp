#include "stdafx.h"
#include "WallModel.h"


WallModel::~WallModel()
{
}

void WallModel::setVisibility(const bool &in_var)
{
	this->visible = in_var;
}

void WallModel::setBoundryWall()
{
	this->boundryWall = true;
}


void WallModel::createBoundingBox()
{
	/*XMFLOAT3 *points = new XMFLOAT3[this->geometry->getVertexCount()];
	for (int i = 0; i < this->geometry->getVertexCount(); i++)
	{
		points[i] = this->geometry->vertices.at(i).pos;
	}
	this->collideBox = CollisionBox(points, this->geometry->getVertexCount());*/
	
}

bool WallModel::isVisible() const
{
	return this->visible;
}

bool WallModel::getBoundryWall() const
{
	return this->boundryWall;
}


DirectX::XMMATRIX WallModel::getWorldMatrix() const
{
	return this->getWorld();
}

void WallModel::Update()
{
}

void WallModel::Draw(ID3D11DeviceContext * pDevCon, Matrix view, Matrix proj)
{
	for (size_t i = 0; i < m_Meshes.size(); i++)
	{
		m_BasicShader->m_effect->SetMatrices(wMatrix, view, proj);
		m_Meshes[i]->Draw(m_BasicShader);
	}
}
