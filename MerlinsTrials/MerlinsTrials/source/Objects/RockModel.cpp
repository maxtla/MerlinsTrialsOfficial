#include "stdafx.h"
#include "RockModel.h"

RockModel::RockModel(Matrix world, bool isSolid, bool isVisible) : ModelBase(world, isSolid, isVisible)
{

}

RockModel::~RockModel(){}

void RockModel::Draw(BasicShader * pBasicShader)
{
	pBasicShader->m_effect->SetWorld(wMatrix);
	for (size_t i = 0; i < m_Meshes.size(); i++)
	{
		m_Meshes[i]->Draw(pBasicShader);
	}
}

void RockModel::DrawOBBS(BasicShader * pBasicShader, PrimitiveBatch<DirectX::VertexPositionColor> *batch, Matrix view, Matrix proj, Vector4 color)
{
	for (size_t i = 0; i < m_OBBS.size(); i++)
	{
		DebugDraw::Draw(pBasicShader, batch, view, proj,  m_OBBS[i], color);
	}
}