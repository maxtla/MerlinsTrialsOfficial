#ifndef MISCMANAGER_H
#define MISCMANAGER_H
#include<vector>
#include"ModelBase.h"

class MiscManager
{
private:
	std::vector<ModelBase>* models;
	
public:
	MiscManager();
	~MiscManager();

	void initialize(ID3D11Device * in_device, ID3D11DeviceContext * in_deviceContext);
	void setModelPtr(std::vector<ModelBase>* in_models);


};
#endif // !MISCMANAGER_H
