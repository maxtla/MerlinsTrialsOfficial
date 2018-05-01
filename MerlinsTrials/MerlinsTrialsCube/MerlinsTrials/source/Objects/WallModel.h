#pragma once
#ifndef WALLMODEL_H
#define WALLMODEL_H
#include "ModelBase.h"
#include "..\Collision\CollisionBox.h"
#include "..\Shaders\BasicShader.h"
#include "..\Shaders\NormalMapShader.h"


class WallModel : public ModelBase
{
private:
	CollisionBox collideBox; //keeps obb
	bool boundryWall = false;
	bool visible = true;
	BasicShader * m_BasicShader;
	NormalMapShader * m_NormalMapShader;

public:
	WallModel(DirectX::XMMATRIX world) : ModelBase(world, true, true){}
	~WallModel();

	void setBasicShader(BasicShader * in_Shader) { this->m_BasicShader = in_Shader; }
	void setNormalMapShader(NormalMapShader * in_Shader) { this->m_NormalMapShader = in_Shader; }
	void setVisibility(const bool &in_var);
	void setBoundryWall();
	void createBoundingBox();

	bool isVisible() const;
	bool getBoundryWall() const;
	CollisionBox getBoundingBox() const;
	DirectX::XMMATRIX getWorldMatrix() const;

	void Update();
	void Draw(ID3D11DeviceContext* pDevCon, Matrix view, Matrix proj);
};

#endif // !WALLMODEL_H
