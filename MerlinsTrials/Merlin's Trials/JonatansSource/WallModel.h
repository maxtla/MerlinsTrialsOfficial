#ifndef WALLMODEL_H
#define WALLMODEL_H
#include"ModelBase.h"
#include"CollisionBox.h"

class WallModel : public ModelBase
{
private:
	CollisionBox CollideBox; //keeps obb
	bool visible = true;

public:
	WallModel();
	WallModel(ID3D11Device *in_device, const Geometry* in_geometry);
	WallModel(ID3D11Device *in_device, const DirectX::XMMATRIX &in_wMatrix, const Geometry* in_geometry);
	~WallModel();

	void setGeometry(const Geometry* in_geometry);
	void setWorldMatrix(const DirectX::XMMATRIX &in_wMatrix);
	void createBoundingBox();

	CollisionBox getBoundingBox() const;
	DirectX::XMMATRIX getWorldMatrix() const;
	Geometry* getGeometry() const;
};

#endif // !WALLMODEL_H
