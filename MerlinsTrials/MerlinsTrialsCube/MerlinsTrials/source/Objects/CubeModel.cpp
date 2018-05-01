#include "stdafx.h"
#include "CubeModel.h"
#include "CubeModel.h"

CubeModel::CubeModel(DirectX::XMMATRIX wMatrix, bool isSolid, bool isVisible, int in_id) : ModelBase(wMatrix, isSolid, isVisible)
{
	this->id = in_id;
}

CubeModel::~CubeModel()
{

}

void CubeModel::setNormalMapShader(NormalMapShader * in_shader)
{
	this->m_NormalMapShader = in_shader;
}

DirectX::BoundingOrientedBox CubeModel::getBoundingBox()
{
	return this->m_Meshes[0]->m_bb;
}

float CubeModel::getGrabDistance() const
{
	return this->grabDistance;
}

void CubeModel::makeCollideBox()
{

}

void CubeModel::update()
{

}

void CubeModel::Draw(ID3D11DeviceContext * in_context, Matrix view, Matrix proj)
{
	for (auto var : this->m_Meshes)
	{
		this->m_NormalMapShader->m_effect->SetMatrices(this->wMatrix, view, proj);
		var->Draw(this->m_NormalMapShader);
	}
}
