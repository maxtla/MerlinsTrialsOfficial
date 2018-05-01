#include "stdafx.h"
#include "PedestalModel.h"

PedestalModel::PedestalModel(DirectX::XMMATRIX wMatrix, bool isSolid, bool isVisible, bool canCollide, int id, Color color)
	:ModelBase(wMatrix, isSolid, isVisible, canCollide, id, color)
{
	
}

PedestalModel::~PedestalModel() {

}

void PedestalModel::Update()
{

}

void PedestalModel::Draw(ID3D11DeviceContext * pDevCon, Matrix view, Matrix proj)
{
	for (size_t i = 0; i < m_Meshes.size(); i++)
	{
		m_BasicShader->m_effect->SetMatrices(wMatrix, view, proj);
		m_Meshes[i]->Draw(m_BasicShader);
	}
}