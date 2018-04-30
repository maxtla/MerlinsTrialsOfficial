#include "stdafx.h"
#include "ModelBase.h"
#include "..\Collision\Collision.h"
#include "..\Collision\CollisionBox.h"


ModelBase::~ModelBase()
{
}

bool ModelBase::isCollidingWith(DirectX::BoundingOrientedBox* otherBB)
{
	bool isColliding = false;
	Collision* tempColl = new Collision();

	if (this->canCollide == true)
	{
		isColliding = tempColl->checkCollision(&this->m_bb, otherBB);
	}

	delete tempColl;

	return isColliding;
}

void ModelBase::setWorldMatrix(const DirectX::XMMATRIX & in_wMatrix)
{
	this->wMatrix = in_wMatrix;
}

void ModelBase::createBoundingOrientBox()
{
	size_t vertexCount = 0;
	int nrOfPoints = 0;

	for (int i = 0; i < this->m_Meshes.size(); i++)
	{
		vertexCount += this->m_Meshes.at(i)->getVertexCount();
	}

	DirectX::XMFLOAT3* points = new DirectX::XMFLOAT3[vertexCount];

	for (int i = 0; i < this->m_Meshes.size(); i++)
	{	
		vertexCount = this->m_Meshes.at(i)->getVertexCount();		

		for (int j = 0; j < vertexCount; j++)
		{
			points[nrOfPoints++] = this->m_Meshes.at(i)->vertices_PNT.at(j).position; //Här får vi göra en koll för vilken vertexType det är. Just nu antar jag bara att det är PNT. 
		}			
	}	

	CollisionBox* tempCollB = new CollisionBox(points, vertexCount);
	
	this->m_bb = tempCollB->getBoundingBox;

	delete[] points;
	delete tempCollB;
}


DirectX::XMMATRIX ModelBase::getWorld() const
{
	return this->wMatrix;
}

DirectX::BoundingOrientedBox ModelBase::getBoundingBox()
{
	return this->m_bb;
}

