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
	DirectX::SimpleMath::Color m_color;
	std::vector<Mesh*> m_Meshes;
	std::vector<DirectX::BoundingOrientedBox> m_OBBS;


public:
	ModelBase(DirectX::XMMATRIX wMatrix, bool isSolid, bool isVisible) : wMatrix(wMatrix), isSolid(isSolid), isVisible(isVisible) {}

	virtual ~ModelBase();

	void setWorldMatrix(const DirectX::XMMATRIX &in_wMatrix);
	void setMeshes(std::vector<Mesh*> meshes) { this->m_Meshes = meshes; }
	void createOBBS();
	DirectX::XMMATRIX getWorld() const;
	std::vector<Mesh*> getMeshes() const { return m_Meshes; }
};
#endif // !MODELBASE_H
