#pragma once
#ifndef CUBEMODEL_H
#define CUBEMODEL_H
#include "..\Collision\CollisionBox.h"
#include "..\Helpers\AssetsPaths.h"
#include "..\Importer\Mesh.h"
#include "..\Importer\ObjectImporter.h"
class CubeModel
{
private:

	int id;
	float grabDistance = 15.0f;
	DirectX::XMMATRIX wMatrix;
	bool isSolid;
	bool isVisible;
	bool isOnPedistal;
	Mesh* mesh;
	
	ObjectImporter importer;
	BasicShader * m_BasicShader;
	NormalMapShader * m_NormalMapShader;

public:
	CubeModel(DirectX::XMMATRIX wMatrix, bool isSolid, bool isVisible, int in_id);
	~CubeModel();

	//sets
	void setNormalMapShader(NormalMapShader * in_shader);
	void setBasicShader(BasicShader* in_shader);
	void setVisisble(const bool &in_value);
	void setSolid(const bool &in_value);
	void setWorld(const XMMATRIX &in_matrix);

	//gets
	DirectX::BoundingBox getBoundingBox();
	float getGrabDistance() const;
	int getID() const;
	bool getVisisble() const;
	bool getSolid() const;
	XMMATRIX getWorld() const;

	//miscs
	void update();
	void Draw(ID3D11DeviceContext* in_context, Matrix view, Matrix proj);
	void loadModel(const std::string &path, ID3D11Device* in_device, ID3D11DeviceContext* in_context);

};
#endif