#ifndef OBJECTIMPORTER_H
#define OBJECTIMPORTER_H
#include <assimp\Importer.hpp>
#include"Geometry.h"
#include<VertexTypes.h>

class ObjectImporter
{
private:
	Assimp::Importer importer;
	void debugString(const LPCWSTR &in_string, const aiReturn &in_param);
public:

	ObjectImporter();
	~ObjectImporter();

	bool importModel(const std::string &fname, std::vector<Geometry>& objects); //behöver ändras på!
	bool importOBJModel(const std::string &path, std::vector<Geometry*> &ppGeometry);


};
#endif // !OBJECTIMPORTER_H
