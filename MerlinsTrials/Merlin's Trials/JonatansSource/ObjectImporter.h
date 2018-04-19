#ifndef OBJECTIMPORTER_H
#define OBJECTIMPORTER_H
#include<assimp\Importer.hpp>
#include"Geometry.h"

class ObjectImporter
{
private:
	Assimp::Importer importer;
	void debugString(const LPCSTR &in_string, const aiReturn &in_param);
public:

	ObjectImporter();
	~ObjectImporter();

	bool importModel(const std::string &fname, std::vector<Geometry>& objects);


};
#endif // !OBJECTIMPORTER_H
