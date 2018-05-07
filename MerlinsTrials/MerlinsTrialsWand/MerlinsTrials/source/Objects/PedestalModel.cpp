#include "stdafx.h"
#include "PedestalModel.h"

PedestalModel::PedestalModel(DirectX::XMMATRIX wMatrix, bool isSolid, bool isVisible, int in_id) : ModelBase(wMatrix, isSolid, isVisible)
{
	this->id = in_id;
}

PedestalModel::~PedestalModel()
{
}

void PedestalModel::setBasicShader(BasicShader* in_shader)
{
	this->m_BasicShader = in_shader;
}

void PedestalModel::setNormalMapShader(NormalMapShader * in_shader)
{
	this->m_NormalMapShader = in_shader;
}

DirectX::BoundingBox PedestalModel::getBoundingBox()
{
	return this->m_Meshes[0]->m_AABB;
}

int PedestalModel::getID() const
{
	return this->id;
}

void PedestalModel::update()
{

}

void PedestalModel::Draw(ID3D11DeviceContext * in_context, Matrix view, Matrix proj)
{
	for (auto var : this->m_Meshes)
	{
		this->m_BasicShader->m_effect->SetMatrices(this->wMatrix, view, proj);
		var->Draw(this->m_BasicShader);
	}
}
