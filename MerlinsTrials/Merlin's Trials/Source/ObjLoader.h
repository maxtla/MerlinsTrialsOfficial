#ifndef OBJLOADER_H
#define OBJLOADER_h
#include"assimp\include\assimp\Importer.hpp"
#include"assimp\include\assimp\scene.h"
#include"assimp\include\assimp\postprocess.h"
#include"ObjectMesh.h"
#include<vector>
#include<string>



class ObjLoader
{
private:
	Assimp::Importer lImporter;
	const aiScene* lScene = nullptr;
	ObjectMesh * lMesh = nullptr;

	//functions
	bool loadFile(std::string fName);
	void loadVector();

public:
	ObjLoader();
	~ObjLoader();

	bool importObject(const std::string fileName, std::vector<ObjectMesh> * mesh);

};
#endif // !OBJLOADER_H
