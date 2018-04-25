#include "stdafx.h"
#include "ObjectImporter.h"
#include<windows.h>
#include<iostream>
#include<vector>
#include<assimp\scene.h>
#include<assimp\postprocess.h>


void ObjectImporter::debugString(const LPCWSTR &in_string, const aiReturn &in_param)
{
	if (AI_SUCCESS != in_param)
	{
		OutputDebugString(in_string);
	}
}

ObjectImporter::ObjectImporter()
{
}

ObjectImporter::~ObjectImporter()
{
}

bool ObjectImporter::importModel(const std::string & fname, std::vector<Geometry>& objects){

	const aiScene* nScene = this->importer.ReadFile(fname, aiProcess_Triangulate);
	//const aiScene* nScene = this->importer.ReadFile(fname, NULL);

	//if the importer fails to read the specified file it returns NULL == 0
	if (!nScene)
	{
		OutputDebugString(reinterpret_cast<LPCWSTR>(this->importer.GetErrorString()));
		return false;
	}

	for (UINT32 i = 0; i < nScene->mNumMeshes; i++)
	{

		//Current mesh
		aiMesh * cMesh = nScene->mMeshes[i];
		unsigned int mIndx = cMesh->mMaterialIndex;
		aiMaterial* mtl = nScene->mMaterials[mIndx];
	
		//Current Object
		Geometry tempO;

		//Iterate vertex values for mesh and store them
		for (UINT32 n = 0; n < cMesh->mNumVertices; n++){

			//Vertex struct
			Geometry::Vertex vertex;

			//Copy values
			vertex.pos.x = cMesh->mVertices[n].x;
			vertex.pos.y = cMesh->mVertices[n].y;
			vertex.pos.z = cMesh->mVertices[n].z;

			vertex.norm.x = cMesh->mNormals[n].x;
			vertex.norm.y = cMesh->mNormals[n].y;
			vertex.norm.z = cMesh->mNormals[n].z;

			//vertex.uv.x = cMesh->mTextureCoords[n]->x;
			//vertex.uv.y = cMesh->mTextureCoords[n]->y;

			//Store vertex
			tempO.addVertex(vertex);
		}

		//Iterate indices and store them
		for (UINT32 k = 0; k < cMesh->mNumFaces; k++)
		{
			
			for (UINT32 j = 0; j < cMesh->mFaces[k].mNumIndices; j++)
			{
				//save indices
				tempO.addIndex(cMesh->mFaces[k].mIndices[j]);
			}
		}

		//Vertex/Face count
		tempO.setVertexCount(cMesh->mNumVertices);
		tempO.setFaceCount(cMesh->mNumFaces);

		//save current mesh name
		tempO.setName(cMesh->mName.C_Str());

		//grab colorinformation
		aiReturn rValue;
		aiString aiPath;
		DirectX::SimpleMath::Vector3 vec3;
		aiColor3D cColor(0.0f, 0.0f, 0.0f);
		float nsSpecularExponent = 0.0f;
		float dOpacity = 0.0f;
	
		rValue = mtl->Get(AI_MATKEY_SHININESS, nsSpecularExponent);
		tempO.setSpecExponent(nsSpecularExponent);
		this->debugString(LPCWSTR("NS failed import"), rValue);

		mtl->Get(AI_MATKEY_OPACITY, dOpacity);
		tempO.setOpacity(dOpacity);
		this->debugString(LPCWSTR("dOpacity failed import"), rValue);

		mtl->Get(AI_MATKEY_COLOR_DIFFUSE, cColor);
		vec3 = DirectX::SimpleMath::Vector3(cColor.r, cColor.g, cColor.b);
		tempO.setDiffuse(vec3);
		this->debugString(LPCWSTR("cDiffuse failed import"), rValue);

		mtl->Get(AI_MATKEY_COLOR_AMBIENT, cColor);
		vec3 = DirectX::SimpleMath::Vector3(cColor.r, cColor.g, cColor.b);
		tempO.setAmbient(vec3);
		this->debugString(LPCWSTR("cAmbient failed import"), rValue);

		mtl->Get(AI_MATKEY_COLOR_SPECULAR, cColor);
		vec3 = DirectX::SimpleMath::Vector3(cColor.r, cColor.g, cColor.b);
		tempO.setSpec(vec3);
		this->debugString(LPCWSTR("cSpecular failed import"), rValue);

		mtl->Get(AI_MATKEY_COLOR_EMISSIVE, cColor);
		vec3 = DirectX::SimpleMath::Vector3(cColor.r, cColor.g, cColor.b);
		tempO.setEmissive(vec3);
		this->debugString(LPCWSTR("cEmissive failed import"), rValue);

		mtl->GetTexture(aiTextureType_DIFFUSE, 0, &aiPath);
		tempO.setDifTexPath(aiPath.C_Str());
		this->debugString(LPCWSTR("tPath diffuse failed import"), rValue);

		mtl->GetTexture(aiTextureType_NORMALS, 0, &aiPath);
		tempO.setNormTexPath(aiPath.C_Str());
		this->debugString(LPCWSTR("tPath normals failed import"), rValue);

		objects.push_back(tempO);

	}
	
	//return function
	return true;
}

bool ObjectImporter::importOBJModel(const std::string & path, std::vector<Geometry*> &ppGeometry)
{
	const ::aiScene* t_scene = this->importer.ReadFile(path.c_str(), aiProcess_Triangulate);

	if (!t_scene)
	{
		OutputDebugString(reinterpret_cast<LPCWSTR>(this->importer.GetErrorString()));
		return false;
	}

	if (!t_scene->HasMeshes())
		throw std::runtime_error("ERROR: Loaded object contained no meshes.\n");

	ppGeometry.reserve(t_scene->mNumMeshes);

	for (UINT32 i = 0; i < t_scene->mNumMeshes; i++)
	{
		ppGeometry[i] = new Geometry();
		::aiMesh* t_mesh = t_scene->mMeshes[i];
		unsigned int mIndx = t_mesh->mMaterialIndex;
		aiMaterial* mtl = t_scene->mMaterials[mIndx];

		ppGeometry[i]->setName(t_mesh->mName.C_Str());

		//handle the faces and fill the index buffer
		if (t_mesh->HasFaces())
		{
			::aiFace *t_faces = t_mesh->mFaces;
			int numOfFaces = t_mesh->mNumFaces;
			ppGeometry[i]->indices.reserve(t_mesh->mNumFaces * 3); //allocate memory

			for (UINT32 j = 0; j < t_mesh->mNumFaces; j++)
			{
				if (t_faces[j].mNumIndices != 3)
				{
					importer.FreeScene();
					throw std::runtime_error("ERROR: Mesh not triangulated.");
				}
				
				for (UINT32 k = 0; k < 3; k++)
				{
					ppGeometry[i]->indices[j * 3 + k] = t_faces[j].mIndices[k];
				}
			}
		}

		ppGeometry[i]->setFaceCount(t_mesh->mNumFaces);
	
		//if pos, normal and uvs are present, load int that vertextype
		if (t_mesh->HasPositions() && t_mesh->HasNormals() && t_mesh->HasTextureCoords(0))
		{
			ppGeometry[i]->vertices_PNT.reserve(t_mesh->mNumVertices); //allocate memory
			ppGeometry[i]->setVertexCount(t_mesh->mNumVertices);

			for (UINT32 m = 0; m < t_mesh->mNumVertices; m++)
			{
				DirectX::VertexPositionNormalTexture t_pnt;
				t_pnt.position = DirectX::XMFLOAT3(t_mesh->mVertices[m].x, t_mesh->mVertices[m].y, t_mesh->mVertices[m].z);
				t_pnt.normal = DirectX::XMFLOAT3(t_mesh->mNormals[m].x, t_mesh->mNormals[m].y, t_mesh->mNormals[m].z);
				t_pnt.textureCoordinate = DirectX::XMFLOAT2(t_mesh->mTextureCoords[m]->x, t_mesh->mTextureCoords[m]->y);

				//add the vertex to the correct vector
				ppGeometry[i]->vertices_PNT[m] = t_pnt;
			}
		}

	}

}
