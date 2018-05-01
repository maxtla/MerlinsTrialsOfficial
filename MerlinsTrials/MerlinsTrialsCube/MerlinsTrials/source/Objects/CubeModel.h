#pragma once
#ifndef CUBEMODEL_H
#define CUBEMODEL_H
#include "..\Objects\ModelBase.h"
#include "..\Collision\CollisionBox.h"
class CubeModel : public ModelBase
{
private:
	int id;
	bool visible = true;
	float grabDistance = 15.0f;

	BasicShader * m_BasicShader;
	NormalMapShader * m_NormalMapShader;

public:
	CubeModel(DirectX::XMMATRIX wMatrix, bool isSolid, bool isVisible, int in_id);
	~CubeModel();
	 
	void setNormalMapShader(NormalMapShader * in_shader);
	DirectX::BoundingOrientedBox getBoundingBox();
	float getGrabDistance() const;
	void update();
	void Draw(ID3D11DeviceContext* in_context, Matrix view, Matrix proj);
};
#endif