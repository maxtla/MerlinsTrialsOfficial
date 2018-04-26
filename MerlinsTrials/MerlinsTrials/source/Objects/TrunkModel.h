#ifndef TRUNKMODEL_H
#define TRUNKMODEL_H
#include "ModelBase.h"
#include "..\Importer\Geometry.h"
#include "..\Collision\CollisionBox.h"

class TrunkModel : public ModelBase
{
private:
	CollisionBox collideBox;

public:
	TrunkModel(Geometry * in_var, ID3D11DeviceContext* in_context);
	~TrunkModel();

	CollisionBox getBoundingBox() const;

};
#endif // !TRUNKMODEL_H
