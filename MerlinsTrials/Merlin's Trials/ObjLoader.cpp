#include "stdafx.h"
#include "ObjLoader.h"

ObjLoader::ObjLoader()
{

}

ObjLoader::~ObjLoader()
{
}

bool ObjLoader::importObject(const std::string fileName, std::vector<ObjectMesh> * outMesh)
{
	if (!this->loadFile(fileName))
	{
		//return something went wrong
		return false;
	}

	this->loadVector();

	//assign pointer to mesh data
	
	return true;
}

bool ObjLoader::loadFile(std::string fName)
{
	//reads obj and flips everything from right handed to left handed
	this->lScene = this->lImporter.ReadFile(fName, aiProcess_MakeLeftHanded | aiProcess_Triangulate);

	if (this->lScene != NULL)
	{
		//failed to load file
		//output to VS debugg window
		OutputDebugString(reinterpret_cast<LPCWSTR>(*this->lImporter.GetErrorString()));
		return false;
	}

	//object loaded and ready for use
	return true;
}

void ObjLoader::loadVector()
{
	//allocate new vector to be returned
	aiColor3D color;
	DirectX::SimpleMath::Vector3 colorVec;
	
	ObjectMesh::Vertex vertex;
	std::vector<ObjectMesh::Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<DirectX::SimpleMath::Vector3> materials;

	for (unsigned int i = 0; i < this->lScene->mNumMeshes; i++)
	{
		vertex.position.x = this->lScene->mMeshes[i]->mVertices->x;
		vertex.position.y = this->lScene->mMeshes[i]->mVertices->y;
		vertex.position.z = this->lScene->mMeshes[i]->mVertices->z;
		
		vertex.normals.x = this->lScene->mMeshes[i]->mNormals->x;
		vertex.normals.y = this->lScene->mMeshes[i]->mNormals->y;
		vertex.normals.z = this->lScene->mMeshes[i]->mNormals->z;
		
		vertices.push_back(vertex);

		if (this->lScene->HasTextures())
		{

			vertex.uvs.x = this->lScene->mMeshes[i]->mTextureCoords[0][i].x;
			vertex.uvs.y = this->lScene->mMeshes[i]->mTextureCoords[0][i].y;
			vertices[i].uvs = vertex.uvs;
			//load textures

		}

		for (unsigned int j = 0; j < this->lScene->mMeshes[i]->mNumFaces; j++)
		{
			for (unsigned int k = 0; k < this->lScene->mMeshes[i]->mFaces->mNumIndices; k++)
			{
				 indices.push_back(this->lScene->mMeshes[i]->mFaces[j].mIndices[k]);
			}
		}

		if (this->lScene->HasMaterials())
		{
			this->lScene->mMaterials[this->lScene->mMeshes[i]->mMaterialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, color);
			colorVec.x = color.r;
			colorVec.y = color.g;
			colorVec.z = color.b;
			materials.push_back(colorVec);
		}

	}



}
