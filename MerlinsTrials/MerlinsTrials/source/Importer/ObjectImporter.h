#ifndef OBJECTIMPORTER_H
#define OBJECTIMPORTER_H
#include<assimp\Importer.hpp>
#include "Mesh.h"
#include <VertexTypes.h>
#include<windows.h>
#include<iostream>
#include<vector>
#include<assimp\scene.h>
#include<assimp\postprocess.h>

class ObjectImporter
{
private:
	Assimp::Importer importer;
	void debugString(const LPCWSTR &in_string, const aiReturn &in_param);

	void _fillWithPos(std::vector<Mesh*> &ppMesh, size_t index, aiMesh* t_mesh, ID3D11Device * pDev);
	void _fillWithPosNorm(std::vector<Mesh*> &ppMesh, size_t index, aiMesh* t_mesh, ID3D11Device * pDev);
	void _fillStaticLevelMesh(std::vector<Mesh*> &ppMesh, size_t index, aiMesh* t_mesh, ID3D11Device * pDev, int flag, float scaling, Vector3 color);
	void _fillWithPosNormTex(std::vector<Mesh*> &ppMesh, size_t index, aiMesh* t_mesh, ID3D11Device * pDev);
	void _fillWithPosNormCol(std::vector<Mesh*> &ppMesh, size_t index, aiMesh* t_mesh, ID3D11Device * pDev);
public:

	ObjectImporter();
	~ObjectImporter();

	bool importOBJModel(const std::string &path, std::vector<Mesh*> &ppMesh, ID3D11Device * pDev, ID3D11DeviceContext * pDevCon);
	bool importLevel(const std::string &path, std::vector<Mesh*> &ppMesh, ID3D11Device * pDev, ID3D11DeviceContext * pDevCon);
	bool importFBXModel(const std::string &path, std::vector<Mesh*> &ppMesh, ID3D11Device * pDev, ID3D11DeviceContext * pDevCon, BOUNDINGTYPE bbFlag = NONE, float scaling = 1.0f);
};
#endif // !OBJECTIMPORTER_H
