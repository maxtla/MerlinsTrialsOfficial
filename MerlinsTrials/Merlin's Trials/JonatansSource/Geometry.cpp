#include"Geometry.h"

Geometry::Geometry() {

	//Shading values
	this->cDif = Vector3(0.0f, 0.0f, 0.0f);
	this->cAmbient = Vector3(0.0f, 0.0f, 0.0f);
	this->cSpec = Vector3(0.0f, 0.0f, 0.0f);
	this->cEmissive = Vector3(0.0f, 0.0f, 0.0f);
	this->specExponent = 0.0f;
	this->opacity = 0.0f;

	//Texture paths
	this->difTexPath = "";
	this->normTexPath = "";

	//Name
	this->meshName = "";

	//Checks
	this->isColliding = false;
	this->isVisisble = false;

}

Geometry::~Geometry() {


}

//////////////////////MISC/////////////////////////
void Geometry::addVertex(Vertex newVertex) {

	this->vertices.push_back(newVertex);

}

void Geometry::addIndex(int newIndex) {

	this->indices.push_back(newIndex);

}


///////////////////////GET///////////////////////////

int Geometry::getVertexCount() const
{
	return this->vertexCount;
}

int Geometry::getFaceCount() const
{
	return this->faceCount;
}

std::string Geometry::getName() const
{
	return this->meshName;
}

//////////////////////////SET////////////////////////////
void Geometry::setDiffuse(const Vector3 &dif) {

	this->cDif = dif;

}

void Geometry::setAmbient(const Vector3 &ambient) {

	this->cAmbient = ambient;

}

void Geometry::setSpec(const Vector3 &spec) {

	this->cSpec = spec;

}

void Geometry::setEmissive(const Vector3 &emissive) {

	this->cEmissive = emissive;

}

void Geometry::setSpecExponent(const float &specExponent) {

	this->specExponent = specExponent;

}

void Geometry::setOpacity(const float &opacity) {

	this->opacity = opacity;

}

void Geometry::setName(const std::string &name) {

	this->meshName = name;

}

void Geometry::setDifTexPath(const std::string &path) {

	this->difTexPath = path;

}

void Geometry::setNormTexPath(const std::string &path) {

	this->normTexPath = path;

}

void Geometry::setVertexCount(const unsigned int & in_count)
{
	this->vertexCount = in_count;
}

void Geometry::setFaceCount(const unsigned int & in_count)
{
	this->faceCount = in_count;
}
