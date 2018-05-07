#pragma once
#ifndef PEDESTALMODEL_H
#define PEDESTALMODEL_H
#include"ModelBase.h"

class PedestalModel : public ModelBase
{
private:
	int id;

	BasicShader * m_BasicShader;
	NormalMapShader * m_NormalMapShader;
public:
	PedestalModel(DirectX::XMMATRIX wMatrix, bool isSolid, bool isVisible, int in_id);
	~PedestalModel();

	void setNormalMapShader(NormalMapShader * in_shader);
	void setBasicShader(BasicShader* in_shader);
	DirectX::BoundingBox getBoundingBox();
	int getID() const;
	void update();
	void Draw(ID3D11DeviceContext* in_context, Matrix view, Matrix proj);


};

#endif // !PEDESTALMODEL_H
