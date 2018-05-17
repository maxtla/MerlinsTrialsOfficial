#pragma once
#ifndef WALLMODEL_H
#define WALLMODEL_H
#include "ModelBase.h"
#include "..\Shaders\BasicShader.h"
#include <DirectXCollision.h>



class WallModel : public ModelBase
{
private:
	BoundingOrientedBox collideBox; //keeps obb
	bool boundryWall = false;
	bool visible = true;
	BasicShader * m_BasicShader;

public:
	WallModel(DirectX::XMMATRIX world) : ModelBase(world, true, true){}
	~WallModel();

	void setBasicShader(BasicShader * in_Shader) { this->m_BasicShader = in_Shader; }
	void setVisibility(const bool &in_var);
	void setBoundryWall();
	void createBoundingBox();
	bool isVisible() const;
	bool getBoundryWall() const;
	BoundingOrientedBox getBoundingBox() const
	{
		if (m_OBBS.size() != 0)
			return m_OBBS[0];
		else
			throw std::runtime_error("No boundingbox for this wallmodel\n");
	}
	DirectX::XMMATRIX getWorldMatrix() const;

	void Update();
	void Draw(ID3D11DeviceContext* pDevCon, Matrix view, Matrix proj);
};

#endif // !WALLMODEL_H
