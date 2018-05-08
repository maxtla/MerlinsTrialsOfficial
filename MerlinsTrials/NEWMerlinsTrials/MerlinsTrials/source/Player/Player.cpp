#include"stdafx.h"
#include"Player.h"

Player::Player() {
	this->m_basicShader = nullptr;
	this->wand = nullptr;
	this->cam = nullptr;

}

Player::~Player() {
	delete this->m_basicShader;
	delete this->wand;
	delete this->cam;
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
	this->cam->setCameraMoveSpeed(0.0018f);
	this->cam->setRotationalOffset(0.0005f);
	this->cam->setTimerCount(UNLIMITED);
	this->cam->init(hwnd);

	//create a basic shader for the wand model
	m_basicShader = new BasicShader();
	m_basicShader->init(dev, devC);
	m_basicShader->createShader(VertexPosNormCol);

	//load in the wand mesh
	ObjectImporter m_importer;
	std::vector<Mesh*> wandMesh;
	int tryCounter = 0;
RetryPoint:
	if (!m_importer.importFBXModel(WAND_PATH, wandMesh, dev, devC) && tryCounter < 5)
	{
		//flush the vector and reset it, increase try counter
		for (size_t i = 0; i < wandMesh.size(); i++)
			delete wandMesh[i];
		wandMesh.clear();
		tryCounter++;
		goto RetryPoint;
	}
	if (tryCounter == 4)
		return false;
	//Init Wand
	this->wand = new WandModel();
	this->wand->init(wandMesh, m_basicShader, this->dev, this->devC);
	this->wand->createMatrix(this->cam->getCamPos());

	//clear mesh vector from pointers
	wandMesh.clear();

	// Init BoundingBox
	this->avatar = new DirectX::BoundingOrientedBox();
	this->avatar->Extents = DirectX::XMFLOAT3(.1f, .1f, .1f);
	this->avatar->Center = this->cam->getCamPos();

	this->cDimension = Dimension::NORMAL;
	this->cPhase = PUZZLE_PHASE::FIRST;
}

void Player::update(void) 
{

	//Update camera
	this->cam->update();
	this->avatar->Center = this->cam->getCamPos();
	//Update wand
	this->wand->update(this->cam->getView());


	

	if (GetAsyncKeyState(VK_SPACE))
	{
		if (!this->realmKeyPressed)
		{
			this->realmKeyPressed = true;
			this->switchRealm();
		}

	}
	else if (this->realmKeyPressed)
	{
		this->realmKeyPressed = false;
	}

}

void Player::switchRealm()
{
	switch (this->cDimension)
	{
	case Dimension::NORMAL:
		cDimension = Dimension::OTHER;
		break;

	case Dimension::OTHER:
		cDimension = Dimension::NORMAL;
		break;
	}
}

void Player::draw() {

	this->wand->draw(this->cam->getView(), this->cam->getProjection());

}

Dimension Player::getCurrentDimension() const
{
	return this->cDimension;
}

PUZZLE_PHASE Player::getCurrentLevelPhase() const
{
	return this->cPhase;
}

bool Player::getKeyPressed()
{
	return this->holdingKeyPressed;
}

////////////////////////////////GET////////////////////////////////////////////
Camera* Player::getCam(void) {

	return this->cam;

}

WandModel* Player::getWand(void) {

	return this->wand;

}

/////////////////////////////////SET///////////////////////////////////////////
void Player::handleWallCollision(std::vector<DirectX::BoundingOrientedBox> targets)
{
	CollisionBox* originCB = new CollisionBox(*this->avatar);
	CollisionBox* targetCB;
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
}

int Player::synchKey()
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

DirectX::BoundingOrientedBox* Player::Player::getAvatar()
{
	return this->avatar;
}

void Player::setCurrentDimension(const Dimension & in_dim)
{
	this->cDimension = in_dim;
}

void Player::setCurrentLevelPhase(const PUZZLE_PHASE & in_phase)
{
	this->cPhase = in_phase;
}

