#ifndef SPHEREMODEL_H
#define SPHEREMODEL_H
#include"ModelBase.h"
class SphereModel : public ModelBase
{
private:
	DirectX::BoundingSphere bSphere;
	
	void setBoundingSphere();
public:
	SphereModel(const BBType &BoundingType, const DirectX::XMMATRIX &in_wMatrix, const Geometry* in_Geometry);
	~SphereModel();

	DirectX::BoundingSphere getBoundingSphere();

};

#endif // !SPHEREMODEL_H
