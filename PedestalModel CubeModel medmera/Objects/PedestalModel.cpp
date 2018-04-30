#include "PedestalModel.h"

PedestalModel::PedestalModel(DirectX::XMMATRIX wMatrix, bool isSolid, bool isVisible, bool canCollide, int id, Color color)
	:ModelBase(wMatrix, isSolid, isVisible, canCollide, id, color)
{
	
}

PedestalModel::~PedestalModel() {

}
