#ifndef LEAVESMODEL_H
#define LEAVESMODEL_H
#include "ModelBase.h"
#include "..\Importer\Geometry.h"


class LeavesModel : public ModelBase
{
private:


public:
	LeavesModel(Geometry* in_var, ID3D11DeviceContext* in_context);
	~LeavesModel();

};

#endif // !LEAVESMODEL_H
