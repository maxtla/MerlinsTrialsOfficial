#ifndef MODELBASE_H
#define MODEL_BASE_H
#include<DirectXMath.h>
#include"Geometry.h"


class ModelBase
{
protected:
	DirectX::XMMATRIX wMatrix;
	const Geometry * geometry;


public:
	ModelBase();
	ModelBase(const DirectX::XMMATRIX &in_wMatrix, const Geometry* in_Geometry);
	virtual ~ModelBase();

	void setGeometry(const Geometry * in_geometry);
	
	const Geometry* getGeometry() const;
	unsigned int getBoundingBoxType() const;
};
#endif // !MODELBASE_H
