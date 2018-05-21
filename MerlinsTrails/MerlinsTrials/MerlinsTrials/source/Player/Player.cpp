#include"stdafx.h"
#include"Player.h"

Player::Player() {

	this->m_basicShader = nullptr;
	this->wand = nullptr;
	this->cam = nullptr;
	this->inventory = nullptr;
}

Player::~Player() {

	delete this->m_basicShader;
	delete this->wand;
	delete this->cam;
	delete this->inventory;
	delete this->avatar;
}

////////////////////////////////MISC/////////////////////////////////
void Player::terrainCollision(std::vector<Vector3> &vPos,
	std::vector<uint16_t> &indices) {

	//World matrix and camera in terrain local space
	DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
	Vector3 camPos = this->cam->getCamPos();
	camPos.y += 50.0f;
	camPos = DirectX::XMVector3Transform(camPos,
		DirectX::XMMatrixInverse(&DirectX::XMMatrixDeterminant(world), world));

	bool stopSearch = false;
	float dist = 0.0f;
	Vector3 v[3];
	for (int i = 0; i < indices.size() && !stopSearch; i+=3) {

		//Triangle vertices
		v[0] = vPos[indices[i]];
		v[1] = vPos[indices[i + 1]];
		v[2] = vPos[indices[i + 2]];

		//Do a triangle test
		if (DirectX::TriangleTests::Intersects(camPos, { 0, -1, 0 }, v[0], v[1], v[2], dist)) {

			float height = 0.0f;

			//Interpolate using barycentric coords
			float weightV1 = (((v[1].z - v[2].z) * (camPos.x - v[2].x)) + 
				((v[2].x - v[1].x) * (camPos.z - v[2].z))) / 
				(((v[1].z - v[2].z) * (v[0].x - v[2].x)) +
				((v[2].x - v[1].x) * (v[0].z - v[2].z)));

			float weightV2 = (((v[2].z - v[0].z) * (camPos.x - v[2].x)) +
				((v[0].x - v[2].x) * (camPos.z - v[2].z))) /
				(((v[1].z - v[2].z) * (v[0].x - v[2].x)) +
				((v[2].x - v[1].x) * (v[0].z - v[2].z)));

			float weightV3 = 1.0f - weightV1 - weightV2;

			height = ((weightV1 * v[0].y) + (weightV2 * v[1].y) + (weightV3 * v[2].y)) /
				(weightV1 + weightV2 + weightV3);

			//height = (v[0].y + v[1].y + v[2].y) / 3.0f;

			//Send y value to camera
			height = Vector3::Transform({ 0.0f, height, 0.0f }, world).y;
			this->cam->setTerrainHeight(height);
			stopSearch = true;

		}

	}

}

bool Player::init(ID3D11Device* dev, ID3D11DeviceContext* devC, HWND hwnd) {
	//Store D3D11 stuff
	this->dev = dev;
	this->devC = devC;

	//Init camera
	this->cam = new Camera();
	this->cam->createViewMatrix(Vector3(6.5f, 0.5f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
	this->cam->createProjectionMatrix(DirectX::XM_PI * 45 / 180.f, 16 / 9.f, 0.01f, 100.f);
	this->cam->createFrustrum();
	this->cam->setCameraMoveSpeed(0.0018f);
	this->cam->setRotationalOffset(0.0005f);
	this->cam->setTimerCount(UNLIMITED);
	this->cam->init(hwnd);
	this->cam->setCameraYaw(-XM_PI / 2);
	//create a basic shader for the wand model
	m_basicShader = new BasicShader();
	m_basicShader->init(this->dev, this->devC);
	m_basicShader->createShader(VertexPosNormCol);

	//load in the wand mesh
	ObjectImporter m_importer;
	std::vector<Mesh*> wandMesh;
	int tryCounter = 0;
RetryPointWand:
	if (!m_importer.importFBXModel(WAND_PATH, wandMesh, dev, devC) && tryCounter < 5)
	{
		//flush the vector and reset it, increase try counter
		for (size_t i = 0; i < wandMesh.size(); i++)
			delete wandMesh[i];
		wandMesh.clear();
		tryCounter++;
		goto RetryPointWand;
	}
	if (tryCounter == 4)
		return false;

	//Init Wand
	this->wand = new WandModel();
	this->wand->init(wandMesh, m_basicShader, this->dev, this->devC);
	this->wand->createMatrix(this->cam->getCamPos());

	//clear mesh vector from pointers
	wandMesh.clear();

	//load in the inventory mesh
	ObjectImporter inv_importer;
	std::vector<Mesh*> invMesh;
	tryCounter = 0;
	
RetryPointInv:
	if (!inv_importer.importFBXModel(INVENTORY_PATH, invMesh, dev, devC) && tryCounter < 5)
	{
		//flush the vector and reset it, increase try counter
		for (size_t i = 0; i < invMesh.size(); i++)
			delete invMesh[i];
		invMesh.clear();
		tryCounter++;
		goto RetryPointInv;
	}
	if (tryCounter == 4)
		return false;

	//Init inventory
	this->inventory = new Inventory();
	this->inventory->init(invMesh, m_basicShader, this->dev, this->devC);

	// Init BoundingBox
	this->avatar = new DirectX::BoundingOrientedBox();
	this->avatar->Extents = DirectX::XMFLOAT3(.05f, .05f, .05f);
	this->avatar->Center = this->cam->getCamPos();

	return true;
}

void Player::update(void) {

	this->lastFramePos = this->cam->getCamPos();

	//Update camera
	this->cam->update();
	this->avatar->Center = this->cam->getCamPos();
	//Update wand
	this->wand->update(this->cam->getView());

	//Update inventory
	this->inventorySelect();
	this->inventory->update(this->cam->getView());

	////Update dimension
	//if (GetAsyncKeyState(VK_SPACE))
	//{
	//	if (!this->realmKeyPressed)
	//	{
	//		this->realmKeyPressed = true;
	//		this->switchRealm();
	//	}

	//}
	//else if (this->realmKeyPressed)
	//{
	//	this->realmKeyPressed = false;
	//}

}

void Player::inventorySelect(void) {

	if (GetAsyncKeyState(0x31)){
		
		this->inventory->setSelected(0);

	}
	else if (GetAsyncKeyState(0x32)) {

		this->inventory->setSelected(1);

	}
	else if (GetAsyncKeyState(0x33)) {

		this->inventory->setSelected(2);

	}
	else if (GetAsyncKeyState(0x34)) {

		this->inventory->setSelected(3);

	}

}

void Player::switchRealm(LevelState* state)
{
	switch (state->getDimension())
	{
	case Dimension::NORMAL:
		state->setDimension(Dimension::OTHER);
		break;

	case Dimension::OTHER:
		state->setDimension(Dimension::NORMAL);
		break;
	}
}

void Player::draw() {

	//Draw wand
	this->wand->draw(this->cam->getView(), this->cam->getProjection());

	//Draw inventory
	this->inventory->draw(this->cam->getView(), this->cam->getProjection());

}

////////////////////////////////GET////////////////////////////////////////////
Camera* Player::getCam(void) {

	return this->cam;

}

WandModel* Player::getWand(void) {

	return this->wand;

}

bool Player::getKeyPressed()
{
	return this->holdingKeyPressed;
}


/////////////////////////////////SET///////////////////////////////////////////
void Player::handleWallCollision(std::vector<DirectX::BoundingOrientedBox> targets)
{
	CollisionBox* originCB = new CollisionBox(*this->avatar);
	CollisionBox* targetCB = new CollisionBox();
	int faceIndex;
	DirectX::XMVECTOR normalN;
	float depth;
	DirectX::XMVECTOR direction;
	std::vector<XMVECTOR> directions;

	for (auto target : targets)
	{
		targetCB = new CollisionBox(target);
		faceIndex = targetCB->getClosestFace(originCB);
		Faces closestFace = targetCB->getFaceAt(faceIndex);  //Only front, back, left and right sides works.
		Faces closestPlayerFace = originCB->getFaceAt(originCB->getOppositeFaceIndex(faceIndex));
		normalN = DirectX::XMVector3Normalize(closestFace.normal);
		DirectX::XMVECTOR Projection = DirectX::XMVectorMultiply(normalN, DirectX::XMVector3Dot(DirectX::XMLoadFloat3(&closestFace.centerPos), normalN));
		DirectX::XMVECTOR ProjectionPlayer = DirectX::XMVectorMultiply(normalN, DirectX::XMVector3Dot(DirectX::XMLoadFloat3(&closestPlayerFace.centerPos), normalN));
		DirectX::XMVECTOR diff = DirectX::XMVectorSubtract(ProjectionPlayer, Projection);
		depth = sqrtf(DirectX::XMVectorGetX(DirectX::XMVector3Dot(diff, diff)));
		direction = DirectX::XMVectorScale(normalN, depth);
		directions.push_back(direction);
	}
	XMVECTOR finalDirection = XMVECTOR();
	for (int i = 0; i < directions.size(); i++)
	{
		finalDirection = XMVectorAdd(finalDirection, directions.at(i));
	}
	
	DirectX::XMFLOAT3 pos = this->avatar->Center;
	DirectX::XMVECTOR newPos = DirectX::XMVectorAdd(XMLoadFloat3(&pos), finalDirection);
	DirectX::XMStoreFloat3(&pos, newPos);

	this->avatar->Center = pos;
	this->cam->setCameraPosition(pos);
	delete originCB;
	delete targetCB;
}

DirectX::BoundingOrientedBox* Player::Player::getAvatar()
{
	return this->avatar;
}

Inventory * Player::getInventory() const
{
	return this->inventory;
}

int Player::synchGrabKey()
{
	if (GetAsyncKeyState(KEY::E))
	{
		if (!this->holdingKeyPressed)
		{
			this->holdingKeyPressed = true;
			return 1;
		}		
	}
	else if (this->holdingKeyPressed)
	{
		this->holdingKeyPressed = false;

	}
	return 0;
}

int Player::synchRealmKey(LevelState* state)
{
	if (GetAsyncKeyState(KEY::Space))
	{
		if (!this->realmKeyPressed)
		{
			this->realmKeyPressed = true;
			this->switchRealm(state);
			return 1;
		}
	}
	else if (this->realmKeyPressed)
	{
		this->realmKeyPressed = false;

	}
	return 0;
}

void Player::resetToLastFramePos()
{
	this->cam->setCameraPosition(this->lastFramePos);
	this->avatar->Center = this->lastFramePos;
}

void Player::resetPlayer(const DirectX::SimpleMath::Vector3 &in_val)
{
	this->cam->setCameraPosition(in_val);
	this->cam->setCameraTarget(DefaultForward);
	this->cam->setCameraYaw(-XM_PI / 2);
	this->cam->setCameraPitch(0.f);
}
