#ifndef MANAGERBASE_H
#define MANAGERBASE_H
#include"..\Player\Player.h"
#include"..\Shaders\Shaders.h"

class ManagerBase
{
protected:
	
	//common components
	Shaders shaderComponent;
	ID3D11Buffer* cb;
	Player* player;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	Shaders shaderComponent;

	struct Matrices
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};
	Matrices matrices;


	//common functions
	void createCB();
	void rebindCB();

	//interface
	virtual void createModels() = 0;

public:
	ManagerBase();
	ManagerBase(Player* in_player, ID3D11Device* in_device, ID3D11DeviceContext * in_context);
	~ManagerBase();

	virtual void DrawModels() = 0;
};
#endif // !MANAGERBASE_H
