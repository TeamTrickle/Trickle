#include "Player.h"

//��������//-----------------------------------------------------------------------------
void Player::Initialize()
{
	Object::CreateObject(Cube, Vec2(100.f, 200.0f), Vec2(64.0f, 64.0f), 0.0f);

	std::cout << "Player������" << std::endl;
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
//��������//-----------------------------------------------------------------------------
void Player::UpDate()
{
	//���J��������
	float cpx = float(est.x);
	float cpy = float(est.y);
	if (gameEngine->in.Pad_Connection) {
		Vec2 cameraest = { 0,0 };
		cameraest.x = cpx;
		cameraest.y = cpy;
	}
	gameEngine->camera->MovePos(Vec2(cpx, 0.0f));
	gameEngine->camera->MovePos(Vec2(0.0f, cpy));


	//�L�����N�^�[�̈ړ�����
	est.x = 0;

	if (InputLeft()) {
		est.x = -Player::MOVE_SPEED;
		//�L�����N�^�[�̌����ϊ�
		direction = Direction::LEFT;
	}
	if (InputRight()) {
		est.x = Player::MOVE_SPEED;
		//������RIGHT��
		direction = Direction::RIGHT;
	}

	//��q����
	LadderMove();

	// �o�P�b�c����
	if (bucket) {
		switch (direction) {
		//case Direction::LEFT:	bucket->position = this->position - Vec2(bucket->Scale.x, 0.f);	break;
		//case Direction::RIGHT:	bucket->position = this->position + Vec2(bucket->Scale.x, 0.f);	break;
		//�o�P�c�̈ʒu�𓪏�ɕύX
		case Direction::LEFT:	bucket->position = this->position - Vec2(0.0f, bucket->Scale.y);	break;
		case Direction::RIGHT:	bucket->position = this->position - Vec2(0.0f, bucket->Scale.y);	break;
		}
		/*if (Input::KeyInputDown(BUCKET_SPOIL_KEY))
			bucket->Spill();*/
	}

	//y�����̑��x�ɏd�͉����x�������
	if (CheckGravity) {
		est.y += Player::GRAVITY;
	}
	//�W�����v����
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
//��������//-----------------------------------------------------------------------------
void Player::Render()
{
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src(0, 0, 128, 128);
	//LEFT�����Ȃ�摜�𔽓]������
	if (direction == Direction::LEFT) {
		int k = src.w;
		src.w = src.x;
		src.x = k;
	}
	this->playerimg.Draw(draw, src);
}
//��������//-----------------------------------------------------------------------------
void Player::Finalize()
{
	std::cout << "Player���" << std::endl;
	this->playerimg.Finalize();

}
//��������//-----------------------------------------------------------------------------
void Player::Register(CollisionManager* cm) {
	*cm += this;
	*cm += &(this->footBase);
	*cm += &(this->headBase);
	*cm += &(this->leftBase);
	*cm += &(this->rightBase);
}
//��������//-----------------------------------------------------------------------------
//�֐�
//��������//-----------------------------------------------------------------------------
//�W�����v�̏���
void Player::JumpMove()
{
	//������true�̎��͒ʏ���
	if (footBase.isCollided) {
		est.y = 0.f;
		//Z�{�^���������A�W�����v��ԂɈڍs����
		if (gameEngine->in.on(Input::B1,0)) {
			est.y = Player::JUMP_POWER;
		}
		//�㏸��
		if (headBase.isCollided) {
			est.y = 0.0f;	//�㏸�͂𖳌��ɂ���
		}
	}
}
//��������//-----------------------------------------------------------------------------
//�����ڐG����
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
//��������//-----------------------------------------------------------------------------
//���ڐG����
void Player::CheckHead()
{
	headBase.CreateObject(Cube, Vec2(this->position.x, this->position.y + 1.f), Vec2(this->Scale.x, 1.f), 0.0f);
	headBase.objectTag = "PlayerHead";
	headBase.CollisionProcess = [&](const Object& o_) {
		//std::cout << o_.objectTag << std::endl;
		//�����蔻��ɒʂ邩���f����
		if (isWalkable(o_.objectTag)) {
			//std::cout << "�����蒆" << std::endl;
			headBase.isCollided = true;
			this->est.y = 0.f;
		}
	};
}
//��������//-----------------------------------------------------------------------------
void Player::CheckLeft()
{
	leftBase.CreateObject(Cube, Vec2(this->position.x - 1.0f, this->position.y), Vec2(1.f, this->Scale.y), 0.0f);
	leftBase.objectTag = "PlayerLeft";
	leftBase.CollisionProcess = [&](const Object& o_) {
		if (isWalkable(o_.objectTag)) {
			est.x = 0.f;
			leftBase.isCollided = true;
		}
	};
}
//��������//-----------------------------------------------------------------------------
void Player::CheckRight()
{
	rightBase.CreateObject(Cube, Vec2(this->position.x, this->position.y), Vec2(1.f, this->Scale.y), 0.0f);
	rightBase.objectTag = "PlayerRight";
	rightBase.CollisionProcess = [&](const Object& o_) {
		if (isWalkable(o_.objectTag)) {
			est.x = 0.f;
			rightBase.isCollided = true;
		}
	};
}
//��������//-----------------------------------------------------------------------------
bool Player::isWalkable(std::string t) {
	for (auto& s : WALKABLE_CHIPS)
		if (t == s)
			return true;
	return false;
}
//��������//-----------------------------------------------------------------------------
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
//��������//-----------------------------------------------------------------------------
//��q����
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
		//std::cout << "�͂���HIT" << std::endl;
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
