#pragma once
#ifndef MODELBASE_H
#define MODEL_BASE_H
#include <DirectXCollision.h>
#include<DirectXMath.h>
#include <d3d11.h>
#include "SimpleMath.h"
#include <vector>
#include "..\Importer\Mesh.h"

class ModelBase
{
protected:

	DirectX::XMMATRIX wMatrix;
	bool isSolid;
	bool isVisible;
	bool canCollide;
	int id;
	DirectX::SimpleMath::Color m_color;
	DirectX::BoundingOrientedBox m_bb;
	std::vector<Mesh*> m_Meshes;

	void createBoundingOrientBox();
public:
	ModelBase(DirectX::XMMATRIX wMatrix, bool isSolid, bool isVisible, bool canCollide, int id, Color m_color) 
		: wMatrix(wMatrix), isSolid(isSolid), isVisible(isVisible), canCollide(canCollide), id(id), m_color(m_color) {}

	virtual ~ModelBase();

	bool isCollidingWith(DirectX::BoundingOrientedBox* otherBB);
	void setWorldMatrix(const DirectX::XMMATRIX &in_wMatrix);
	void setMeshes(std::vector<Mesh*> meshes) { this->m_Meshes = meshes; }
	void setColor(Color in_Color) { this->m_color = in_Color; };
	DirectX::XMMATRIX getWorld() const;
	DirectX::BoundingOrientedBox getBoundingBox();
};
#endif // !MODELBASE_H
