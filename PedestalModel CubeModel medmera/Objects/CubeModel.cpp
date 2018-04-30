#include "CubeModel.h"

CubeModel::CubeModel(DirectX::XMMATRIX wMatrix, bool isSolid, bool isVisible, bool canCollide, int id, Color m_color)
	:ModelBase(wMatrix, isSolid, isVisible, canCollide, id, m_color)
{

}

CubeModel::~CubeModel()
{

}