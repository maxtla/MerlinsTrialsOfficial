#ifndef WANDMODEL_H
#define WANDMODEL_H

#include"ModelBase.h"
#include"..\Helpers\Enumerators.h"
#include"..\Helpers\Timer.h"
#include "..\Engines\SoundEngine.h"

class WandModel : public ModelBase{

private:

	//Projectiles

	//Pos
	Vector3 pos;

	//Misc
	int nrOfMeshes;
	Timer aniTime;
	Timer pickupTime;

	bool wandGoingUp;
	bool inPickupAnimation;

	//D3D11 Stuff
	ID3D11DeviceContext* devC;
	ID3D11Device * dev;

	//Shaders
	BasicShader* shader_Basic;
	NormalMapShader* shader_NormMap;

	//Matrix
	DirectX::XMMATRIX standardMatrix;
	DirectX::XMMATRIX animationMatrix;

	SoundEngine* hej;

	//Private functions
	void followPlayer(DirectX::XMMATRIX view);

public:

	WandModel(DirectX::XMMATRIX world = DirectX::XMMatrixIdentity());
	~WandModel();

	//Misc
	void init(std::vector<Mesh*> meshes, BasicShader* basicS, ID3D11Device* device, ID3D11DeviceContext* deviceC);
	void createMatrix(Vector3 pos);
	void draw(DirectX::XMMATRIX view, DirectX::XMMATRIX projection);
	void update(DirectX::XMMATRIX view);
	void animation();
	void pickupAnimation();
	void resertPickupTimer();
	//Get
	Vector3 getPos(void) const;
	int getNrOfMeshes(void) const;

	//Set
	void setPos(Vector3 pos);
	void setInPickupAnimation(bool value);

};

#endif // !WANDMODEL_H

