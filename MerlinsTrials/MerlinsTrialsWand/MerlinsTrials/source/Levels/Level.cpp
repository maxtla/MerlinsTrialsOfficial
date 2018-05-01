#include "stdafx.h"
#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
	this->m_StaticObjects.clear();
}

bool Level::initialize(std::vector<Mesh*> mesh, BasicShader * pBasicColorShader)
{
	this->m_StaticObjects = mesh;
	this->m_BasicColorShader = pBasicColorShader;
	m_batch = std::make_unique<PrimitiveBatch<DirectX::VertexPositionColor>>(pBasicColorShader->gDeviceContext);
	return true;
}

bool Level::Update()
{
	for (size_t i = 0; i < m_StaticObjects.size(); i++)
	{
		m_StaticObjects[i]->Update(Matrix::Identity);
	}
	return true;
}

void Level::Draw(Matrix view, Matrix projection)
{

	m_BasicColorShader->setBlendState(); //default
	m_BasicColorShader->setDepthStencilState(); //default
	m_BasicColorShader->setRasterizerState(); //default
	m_BasicColorShader->setSamplerState(); //default

	Matrix world = Matrix::CreateRotationZ(DirectX::XM_PI);
	m_BasicColorShader->m_effect->SetMatrices(world, view, projection);

	for (size_t i = 0; i < m_StaticObjects.size(); i++)
	{
		m_StaticObjects[i]->Draw(m_BasicColorShader);
	}

	for (size_t i = 0; i < m_StaticObjects.size(); i++)
	{
		m_StaticObjects[i]->DrawDebugMode(m_batch.get(), Vector4(1.f, 0.f, 0.f, 1.0f));
	}

}
