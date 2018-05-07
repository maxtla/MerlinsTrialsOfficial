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
	Mesh* c_Mesh;

	void createBoundongOrientBox();
public:
	ModelBase(DirectX::XMMATRIX wMatrix, bool isSolid, bool isVisible) : wMatrix(wMatrix), isSolid(isSolid), isVisible(isVisible) { }

	virtual ~ModelBase();
	void setWorldMatrix(const DirectX::XMMATRIX &in_wMatrix);
	void setMeshes(std::vector<Mesh*> meshes);
	void setMeshes(Mesh* c_Mesh);
	DirectX::XMMATRIX getWorld() const;
};
#endif // !MODELBASE_H
