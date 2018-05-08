#include "stdafx.h"
#include "ModelBase.h"



ModelBase::~ModelBase()
{
}

void ModelBase::setVisisble(const bool & in_value)
{
	this->isVisible = in_value;
}

void ModelBase::setWorldMatrix(const DirectX::XMMATRIX & in_wMatrix)
{
	this->wMatrix = in_wMatrix;
}

void ModelBase::createOBBS()
{
	for (size_t i = 0; i < m_Meshes.size(); i++)
	{
		if (m_Meshes[i]->hasOBB)
		{
			m_OBBS.push_back(m_Meshes[i]->m_OBB);
			m_OBBS[m_OBBS.size() - 1].Transform(m_OBBS[m_OBBS.size() - 1], wMatrix);
		}
	}
}


DirectX::XMMATRIX ModelBase::getWorld() const
{
	return this->wMatrix;
}

bool ModelBase::getVisisble() const
{
	return this->isVisible;
}

