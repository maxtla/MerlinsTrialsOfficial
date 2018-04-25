#ifndef TRUNKMODEL_H
#define TRUNKMODEL_H
#include "ModelBase.h"
#include "Geometry.h"
#include "CollisionBox.h"

class TrunkModel : public ModelBase
{
private:
	CollisionBox collideBox;

public:
	TrunkModel(Geometry * in_var);
	~TrunkModel();

	CollisionBox getBoundingBox() const;

};
#endif // !TRUNKMODEL_H
