#include "Player.h"

//?申?申?申?申?申?申?申?申//-----------------------------------------------------------------------------
void Player::Initialize()
{
	Object::CreateObject(Cube, Vec2(100.f, 200.0f), Vec2(64.0f, 64.0f), 0.0f);

	std::cout << "Player" << std::endl;
	this->playerimg.TextureCreate(this->fileName);

	CheckJump = true;
	CheckGravity = true;
	onLadder = false;

	CheckHead();
	CheckFoot();
	CheckLeft();
	CheckRight();

	direction = Direction::RIGHT;

}
//?申?申?申?申?申?申?申?申//-----------------------------------------------------------------------------
void Player::Update()
{
	//?申?申?申J?申?申?申?申?申?申?申?申
	float cpx = float(est.x);
	float cpy = float(est.y);
	if (gameEngine->in.Pad_Connection) {
		Vec2 cameraest = { 0,0 };
		cameraest.x = cpx;
		cameraest.y = cpy;
	}
	gameEngine->camera->MovePos(Vec2(cpx, 0.0f));
	gameEngine->camera->MovePos(Vec2(0.0f, cpy));


	//?申L?申?申?申?申?申N?申^?申[?申����鐃�?申?申?申?申
	est.x = 0;

	if (InputLeft()) {
		est.x = -Player::MOVE_SPEED;
		//?申L?申?申?申?申?申N?申^?申[?申��鐃�?申?申?申��鐃�
		direction = Direction::LEFT;
	}
	if (InputRight()) {
		est.x = Player::MOVE_SPEED;
		//?申?申?申?申?申?申RIGHT?申?申
		direction = Direction::RIGHT;
	}

	//?申?申q?申?申?申?申
	LadderMove();

	// ?申o?申P?申b?申c?申?申?申?申
	if (bucket) {
		switch (direction) {
		//case Direction::LEFT:	bucket->position = this->position - Vec2(bucket->Scale.x, 0.f);	break;
		//case Direction::RIGHT:	bucket->position = this->position + Vec2(bucket->Scale.x, 0.f);	break;
		//?申o?申P?申c?申����u?申?��鐃宿���X
		case Direction::LEFT:	bucket->position = this->position - Vec2(0.0f, bucket->Scale.y);	break;
		case Direction::RIGHT:	bucket->position = this->position - Vec2(0.0f, bucket->Scale.y);	break;
		}
		/*if (Input::KeyInputDown(BUCKET_SPOIL_KEY))
			bucket->Spill();*/
	}

	//y?申?申?申?申?申��鐃�?申x?申��d?申��鐃�?申?申?申x?申?申?申?申?申?申?申
	if (CheckGravity) {
		est.y += Player::GRAVITY;
	}
	//?申W?申?申?申?申?申v?申?申?申?申
	if (CheckJump) {
		JumpMove();
	}

	// Sync collider player
	footBase.position = Vec2(this->position.x + 10.f, this->position.y + this->Scale.y + est.y);
	headBase.position = Vec2(this->position.x, this->position.y - 1.f + est.y);
	leftBase.position = Vec2(this->position.x + est.x - 1.f, this->position.y);
	rightBase.position = Vec2(this->position.x + this->Scale.x + est.x, this->position.y);

	if (!leftBase.isCollided && !rightBase.isCollided)
		position.x += est.x;
	position.y += est.y;
}
//?申?申?申?申?申?申?申?申//-----------------------------------------------------------------------------
void Player::Render()
{
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src(0, 0, 128, 128);
	//LEFT?申?申?申?申?申��鐃醇��鐃�?��]?申?申?申?申?申?申
	if (direction == Direction::LEFT) {
		int k = src.w;
		src.w = src.x;
		src.x = k;
	}
	this->playerimg.Draw(draw, src);
}
//?申?申?申?申?申?申?申?申//-----------------------------------------------------------------------------
void Player::Finalize()
{
	std::cout << "Player" << std::endl;
	this->playerimg.Finalize();

}
//?申?申?申?申?申?申?申?申//-----------------------------------------------------------------------------
void Player::Register(CollisionManager* cm) {
	*cm += this;
	*cm += &(this->footBase);
	*cm += &(this->headBase);
	*cm += &(this->leftBase);
	*cm += &(this->rightBase);
}
//?申?申?申?申?申?申?申?申//-----------------------------------------------------------------------------
//?申��鐃�
//?申?申?申?申?申?申?申?申//-----------------------------------------------------------------------------
//?申W?申?申?申?申?申v?申��鐃�?申?申
void Player::JumpMove()
{
	//?申?申?申?申?申?申true?申��鐃�?申����鐃�?申?申
	if (footBase.isCollided) {
		est.y = 0.f;
		//Z?申{?申^?申?申?申?申?申?申?申?申?申A?申W?申?申?申?申?申v?申?申������s?申?申?申?申
		if (gameEngine->in.on(Input::B1,0)) {
			est.y = Player::JUMP_POWER;
		}
		//?申���?申?申
		if (headBase.isCollided) {
			est.y = 0.0f;	//?申���?申������鐃�?申��鐃�?申?申
		}
	}
}
//?申?申?申?申?申?申?申?申//-----------------------------------------------------------------------------
//?申?申?申?申?申��G?申?申?申?申
void Player::CheckFoot()
{
	footBase.CreateObject(Cube, Vec2(this->position.x + 10.f, this->position.y + this->Scale.y), Vec2(this->Scale.x - 20.f, 1.0f), 0.0f);
	footBase.objectTag = "PlayerFoot";
	footBase.CollisionProcess = [&](const Object& o_) {
		if (isWalkable(o_.objectTag)) {
			float penetrated = (footBase.position.y + footBase.Scale.y) - o_.position.y;
			if (penetrated > 0.f) {
				this->position.y = o_.position.y - o_.Scale.y + 0.5f;
				est.y = 0.f;
			}
			footBase.isCollided = true;
		}
	};
}
//?申?申?申?申?申?申?申?申//-----------------------------------------------------------------------------
//?申?申?申��G?申?申?申?申
void Player::CheckHead()
{
	headBase.CreateObject(Cube, Vec2(this->position.x, this->position.y + 1.f), Vec2(this->Scale.x, 1.f), 0.0f);
	headBase.objectTag = "PlayerHead";
	headBase.CollisionProcess = [&](const Object& o_) {
		//std::cout << o_.objectTag << std::endl;
		//?申?申?申?申?申���?申?申�������?申?申?申f?申?申?申?申
		if (isWalkable(o_.objectTag)) {
			//std::cout << "?申?申?申?申?申��?" << std::endl;
			headBase.isCollided = true;
			this->est.y = 0.f;
		}
	};
}
//?申?申?申?申?申?申?申?申//-----------------------------------------------------------------------------
void Player::CheckLeft()
{
	leftBase.CreateObject(Cube, Vec2(this->position.x - 1.0f, this->position.y), Vec2(1.f, this->Scale.y), 0.0f);
	leftBase.objectTag = "PlayerLeft";
	leftBase.CollisionProcess = [&](const Object& o_) {
		if (isWalkable(o_.objectTag)) {
			est.x = 0.f;
			leftBase.isCollided = true;
		}
		if (o_.objectTag == "Switch") {
			if (gameEngine->in.down(Input::B4, 0)) {
				((Switch&)o_).ON_OFF();
				std::cout << "change" << std::endl;
			}
		}

	};
}
//?申?申?申?申?申?申?申?申//-----------------------------------------------------------------------------
void Player::CheckRight()
{
	rightBase.CreateObject(Cube, Vec2(this->position.x, this->position.y), Vec2(1.f, this->Scale.y), 0.0f);
	rightBase.objectTag = "PlayerRight";
	rightBase.CollisionProcess = [&](const Object& o_) {
		if (isWalkable(o_.objectTag)) {
			est.x = 0.f;
			rightBase.isCollided = true;
		}
		if (o_.objectTag == "Switch") {
			if (gameEngine->in.down(Input::B4, 0)) {
				((Switch&)o_).ON_OFF();
				std::cout << "change" << std::endl;
			}
		}

	};
}
//?申?申?申?申?申?申?申?申//-----------------------------------------------------------------------------
bool Player::isWalkable(std::string t) {
	for (auto& s : WALKABLE_CHIPS)
		if (t == s)
			return true;
	return false;
}
//?申?申?申?申?申?申?申?申//-----------------------------------------------------------------------------
void Player::TakeBucket(Bucket* b_) {
	if (gameEngine->in.down(Input::B2, 0)) {
		if (bucket) {
			bucket->hold = false;
			bucket = nullptr;
		}
		else if (this->hit(*b_)) {
			bucket = b_;
			bucket->hold = true;
		}
	}
}
//?申?申?申?申?申?申?申?申//-----------------------------------------------------------------------------
//?申?申q?申?申?申?申
void Player::LadderMove()
{
	Object::CollisionProcess = [&](const Object& o_) {
		if (o_.objectTag == "Ladder") {
			CheckJump = false;
			CheckGravity = false;
			isCollided = true;
			onLadder = true;
		}
		else {
			CheckGravity = true;
			CheckJump = true;
			onLadder = false;
		}
	};
	if (onLadder == true) {
		//std::cout << "?申��鐃�?申?申HIT" << std::endl;
		est.y = 0;
		if (InputDown()) {
			est.y = Player::MOVE_SPEED;
		}
		if (InputUp()) {
			est.y = (-Player::MOVE_SPEED);
		}
	}
}

void Player::CustomCollision(std::vector<Object*>* objs_)
{
	static bool isLoged = false;
	if (!isLoged) {
		for (auto& o : *objs_)
			std::cout << o->objectTag << std::endl;
		isLoged = true;
	}
}
