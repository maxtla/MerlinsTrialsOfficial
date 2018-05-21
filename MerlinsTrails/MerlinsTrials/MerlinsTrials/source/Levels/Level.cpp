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
	this->debugShader = new BasicShader(this->m_BasicColorShader->gDevice, this->m_BasicColorShader->gDeviceContext, SHADERTYPE::VertexPosCol);

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
	
	if (indexList.empty())
	{
		for (auto object : m_StaticObjects)
		{
			object->Draw(m_BasicColorShader);
		}
	}
	else
	{
		for (size_t i = 0; i < indexList.size(); i++)
		{
			m_StaticObjects[indexList[i]]->Draw(m_BasicColorShader);
		}
	}

#ifndef NDEBUG
	for (size_t i = 0; i < m_StaticObjects.size(); i++)
	{ 
		m_StaticObjects[i]->DrawDebugMode(this->debugShader, 
			m_batch.get(), view, projection, Vector4(1.f, 0.f, 0.f, 1.0f));
	}
#endif
	OutputDebugStringA((std::to_string(indexList.size()) + "\n").c_str());
	this->indexList.clear();
}

bool Level::collisionTest(BoundingOrientedBox * avatar)
{
	for (auto object : this->m_StaticObjects)
	{
		if (object->collisionTest(avatar))
		{
			return true;
		}
	}
	return false;
}

void Level::checkFrustrum(BoundingFrustum * frustrum)
{
	for (size_t i = 0; i < this->m_StaticObjects.size(); i++)
	{
		if (this->m_StaticObjects[i]->collisionTestFrustrum(frustrum))
		{
			this->indexList.push_back(i);
		}
	}
}
