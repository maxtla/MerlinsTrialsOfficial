#ifndef OBJECTIMPORTER_H
#define OBJECTIMPORTER_H
#include <assimp\Importer.hpp>
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
	void _fillWithPosNormTex(std::vector<Mesh*> &ppMesh, size_t index, aiMesh* t_mesh, ID3D11Device * pDev);
public:

	ObjectImporter();
	~ObjectImporter();

	bool importOBJModel(const std::string &path, std::vector<Mesh*> &ppMesh, ID3D11Device * pDev, ID3D11DeviceContext * pDevCon);
};
#endif // !OBJECTIMPORTER_H
