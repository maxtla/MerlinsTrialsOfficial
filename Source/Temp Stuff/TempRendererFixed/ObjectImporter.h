#ifndef OBJECTIMPORTER_H
#define OBJECTIMPORTER_H
#include<assimp\Importer.hpp>
#include"Object.h"

class ObjectImporter
{
private:
	Assimp::Importer importer;
	void debugString(const LPCWSTR &in_string, const aiReturn &in_param);
public:

	ObjectImporter();
	~ObjectImporter();

	bool importModel(const std::string &fname, std::vector<Object>& objects);


};
#endif // !OBJECTIMPORTER_H
