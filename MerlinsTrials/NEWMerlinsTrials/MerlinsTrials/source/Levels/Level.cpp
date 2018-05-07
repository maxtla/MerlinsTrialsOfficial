#include "stdafx.h"
#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
	for (size_t i = 0; i < m_StaticObjects.size(); i++)
		delete m_StaticObjects[i];

	m_StaticObjects.clear();
	m_batch.reset();
	for (size_t i = 0; i < terrainPointIndices.size(); i++)
	{
		terrainPointIndices[i].clear();
		terrainPointVectors[i].clear();
	}
	terrainPointIndices.clear();
	terrainPointVectors.clear();
}

bool Level::initialize(std::vector<Mesh*> mesh, BasicShader * pBasicColorShader)
{
	this->m_StaticObjects = mesh;
	this->m_BasicColorShader = pBasicColorShader;
	m_batch = std::make_unique<PrimitiveBatch<DirectX::VertexPositionColor>>(pBasicColorShader->gDeviceContext);

	//loop through the mesh vector to retrieve the terrain mesh data
	for (size_t i = 0; i < m_StaticObjects.size(); i++)
	{
		if (m_StaticObjects[i]->isTerrain)
		{
			terrainPointIndices.push_back(m_StaticObjects[i]->indices);
			terrainPointVectors.push_back(m_StaticObjects[i]->getTerrainPoints());
		}
	}

	return true;
}

bool Level::Update(Player * player)
{
	//make terrain testing vs player
	for (size_t i = 0; i < terrainPointIndices.size(); i++)
	{
		player->terrainCollision(terrainPointVectors[i], terrainPointIndices[i]);
	}
	return true;
}

void Level::Draw(Matrix view, Matrix projection)
{

	m_BasicColorShader->setBlendState(); //default
	m_BasicColorShader->setDepthStencilState(); //default
	m_BasicColorShader->setRasterizerState(); //default
	m_BasicColorShader->setSamplerState(); //default

	Matrix world = Matrix::Identity;
	m_BasicColorShader->m_effect->SetMatrices(world, view, projection);

	for (size_t i = 0; i < m_StaticObjects.size(); i++)
	{
		m_StaticObjects[i]->Draw(m_BasicColorShader);
	}
#ifndef NDEBUG
	for (size_t i = 0; i < m_StaticObjects.size(); i++)
	{
		m_StaticObjects[i]->DrawDebugMode(m_batch.get(), Vector4(1.f, 0.f, 0.f, 1.0f));
	}
#endif
}
