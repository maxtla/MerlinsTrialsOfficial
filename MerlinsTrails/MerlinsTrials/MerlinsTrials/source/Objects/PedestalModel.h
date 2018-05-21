#pragma once
#ifndef PEDESTALMODEL_H
#define PEDESTALMODEL_H
#include "..\Importer\Mesh.h"
#include "..\Importer\ObjectImporter.h"
class PedestalModel
{
private:
	int id;
	float grabDistance = 1.0f;
	XMMATRIX wMatrix;
	XMMATRIX rotation;
	XMMATRIX translation;
	XMMATRIX scale;

	bool isSolid;
	bool isVisible;
	Mesh* mesh;


	ObjectImporter importer;
	BasicShader * m_BasicShader;
	BasicShader * pDebugShader;
	std::unique_ptr<PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;

	NormalMapShader * m_NormalMapShader;
public:
	PedestalModel(DirectX::XMMATRIX wMatrix, bool isSolid, bool isVisible, int in_id);
	~PedestalModel();

	void loadModel(const std::string &path, ID3D11Device* in_device, ID3D11DeviceContext* in_context);
	void setVisisble(const bool &in_value);
	void setSolid(const bool &in_value);
	void setWorld(const XMMATRIX &in_matrix);
	void setNormalMapShader(NormalMapShader * in_shader);
	void setBasicShader(BasicShader* in_shader);
	
	DirectX::BoundingOrientedBox getBoundingBox();
	int getID() const;
	bool getVisisble() const;
	bool getSolid() const;
	XMMATRIX getWorld() const;
	float getGrabDistance() const;
	void update();
	void Draw(ID3D11DeviceContext* in_context, Matrix view, Matrix proj);


};

#endif // !PEDESTALMODEL_H
