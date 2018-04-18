#ifndef BOXMODEL_H
#define BOXMODEL_H
#include"ModelBase.h"


class BoxModel : public ModelBase
{
private:
	DirectX::BoundingBox bBox;

	void setBoundingBox();
public:
	BoxModel(const BBType &in_BoundingType, const DirectX::XMMATRIX &in_wMatrix, const Geometry* in_Geometry);
	~BoxModel();


	DirectX::BoundingBox getBoundingBox();


};
#endif // !MODEL_H
