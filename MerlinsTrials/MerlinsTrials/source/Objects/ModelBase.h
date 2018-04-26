#pragma once
#ifndef MODELBASE_H
#define MODEL_BASE_H
#include <DirectXCollision.h>
#include<DirectXMath.h>
#include "SimpleMath.h"
#include <vector>
#include "..\Importer\Geometry.h"

class ModelBase
{
protected:
	DirectX::XMMATRIX wMatrix;
	bool isSolid;
	bool isVisible;
	DirectX::SimpleMath::Color m_color;
	DirectX::BoundingOrientedBox m_bb;
	Geometry * pGeometry;
	ID3D11DeviceContext* context;

	void createBoundingOrientBox();
public:
	ModelBase(Geometry * in_geometry, ID3D11DeviceContext* in_context);
	ModelBase(DirectX::XMMATRIX wMatrix, bool isSolid, bool isVisible) : wMatrix(wMatrix), isSolid(isSolid), isVisible(isVisible) {}
	virtual ~ModelBase();

	DirectX::BoundingOrientedBox getBoundingBox() const;
	DirectX::SimpleMath::Color getColor() const;
	Geometry* getGeometry() const;
	bool getVisible() const;
	bool getSolid() const;
	DirectX::XMMATRIX getWorld() const;

	void setGeometry(Geometry* in_adrr);
	void setBoundingBox(const DirectX::BoundingOrientedBox &in_box);
	void setSolid(const bool &value);
	void setVisisble(const bool &value);
	void setWorldMatrix(const DirectX::XMMATRIX &in_wMatrix);
	
};
#endif // !MODELBASE_H
