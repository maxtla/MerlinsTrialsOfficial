#ifndef MODELBASE_H
#define MODEL_BASE_H
#include<DirectXMath.h>
#include"Geometry.h"


class ModelBase
{
public:
	enum BBType{Sphere = 0, OBB = 1};

protected:
	DirectX::XMMATRIX wMatrix;
	unsigned int boundBType;
	const Geometry * geometry;


public:
	ModelBase();
	virtual ~ModelBase();

	void setGeometry(const Geometry * in_geometry);
	void setBoundingType(const BBType &in_type);
	const Geometry* getGeometry();
	unsigned int getBoundingBoxType();
};
#endif // !MODELBASE_H
