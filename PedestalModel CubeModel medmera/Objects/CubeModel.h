#pragma once
#ifndef CUBEMODEL_H
#define CUBEMODEL_H
#include "ModelBase.h"
class CubeModel : public ModelBase
{
private:

public:
	CubeModel(DirectX::XMMATRIX wMatrix, bool isSolid, bool isVisible, bool canCollide, int id, Color m_color);
	~CubeModel();
};
#endif
