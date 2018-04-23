#ifndef MODELBASE_H
#define MODEL_BASE_H
#include<DirectXMath.h>
#include"Geometry.h"


class ModelBase
{
protected:
	DirectX::XMMATRIX wMatrix;
	const Geometry * geometry;

	//Buffers
	ID3D11Buffer* vBuffer;
	ID3D11Buffer* iBuffer;
	ID3D11Device* device;




public:
	ModelBase();
	ModelBase(ID3D11Device *in_device);
	ModelBase(ID3D11Device *in_device, const Geometry* in_geometry);
	ModelBase(ID3D11Device *in_device, const DirectX::XMMATRIX &in_wMatrix, const Geometry* in_Geometry);
	virtual ~ModelBase();

	void setWorldMatrix(const DirectX::XMMATRIX &in_wMatrix);
	void setGeometry(const Geometry * in_geometry);
	
	ID3D11Buffer* getVBuffer() const;
	ID3D11Buffer* getIBuffer() const;
	const Geometry* getGeometry() const;
	bool createBuffers();
};
#endif // !MODELBASE_H
