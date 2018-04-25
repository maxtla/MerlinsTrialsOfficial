#ifndef LEAVESMODEL_H
#define LEAVESMODEL_H
#include "ModelBase.h"
#include "Geometry.h"
#include "CollisionBox.h"

class LeavesModel
{
private:


public:
	LeavesModel(Geometry* in_var);
	~LeavesModel();

	CollisionBox getBoundingBox() const;

};

#endif // !LEAVESMODEL_H
