#ifndef WALLMODEL_H
#define WALLMODEL_H
#include"ModelBase.h"

class WallModel : public ModelBase
{
private:
	DirectX::BoundingBox bBox;

public:
	WallModel();
	WallModel(const DirectX::XMMATRIX &in_wMatrix, const Geometry* in_geometry);
	~WallModel();

	void setGeometry(const Geometry* in_geometry);
	void setWorldMatrix(const DirectX::XMMATRIX &in_wMatrix);
	void createBoundingBox();

	DirectX::BoundingBox getBoundingBox() const;
	DirectX::XMMATRIX getWorldMatrix() const;
	Geometry* getGeometry() const;
};

#endif // !WALLMODEL_H
