#pragma once
#ifndef PEDESTALMODEL_H
#define PEDESTALMODEL_H
#include <vector>
#include "..\Player\Player.h"
#include "ModelBase.h"
#include "..\Collision\Collision.h"
//#include cube

class PedestalModel : public ModelBase
{
//private:	

public:
	PedestalModel(DirectX::XMMATRIX wMatrix, bool isSolid, bool isVisible, bool canCollide, int id, Color color);
	~PedestalModel();	
};


#endif
