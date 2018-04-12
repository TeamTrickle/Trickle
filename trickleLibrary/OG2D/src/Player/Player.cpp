#include "Player.h"

//☆☆☆☆//-----------------------------------------------------------------------------
void Player::Initialize()
{
	Object::CreateObject(Cube, Vec2(100.f, 200.0f), Vec2(64.0f, 64.0f), 0.0f);

	std::cout << "Player初期化" << std::endl;
	this->playerimg.TextureCreate(this->fileName);

	CheckHead();
	CheckFoot();
	CheckLeft();
	CheckRight();

	direction = Direction::RIGHT;
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Player::Update()
{
	//キャラクターの移動処理
	est.x = 0;

	if (InputLeft()) {
		est.x = -Player::MOVE_SPEED;
		//キャラクターの向き変換
		direction = Direction::LEFT;
	}
	if (InputRight()) {
		est.x = Player::MOVE_SPEED;
		//向きをRIGHTに
		direction = Direction::RIGHT;
	}

	// バケッツ処理
	if (bucket) {
		switch (direction) {
		case Direction::LEFT:	bucket->position = this->position - Vec2(bucket->Scale.x, 0.f);	break;
		case Direction::RIGHT:	bucket->position = this->position + Vec2(bucket->Scale.x, 0.f);	break;
		}
		/*if (Input::KeyInputDown(BUCKET_SPOIL_KEY))
			bucket->Spill();*/
	}

	//y方向の速度に加速度を加える
	est.y += Player::GRAVITY;

	JumpMove();

	// Sync collider player
	footBase.position = Vec2(this->position.x + 10.f, this->position.y + this->Scale.y + est.y);
	headBase.position = Vec2(this->position.x, this->position.y - 1.f + est.y);
	leftBase.position = Vec2(this->position.x + est.x - 1.f, this->position.y);
	rightBase.position = Vec2(this->position.x + this->Scale.x + est.x, this->position.y);

	if (!leftBase.isCollided && !rightBase.isCollided)
		position.x += est.x;
	position.y += est.y;
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Player::Render()
{
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src(0, 0, 128, 128);
	//LEFT向きなら画像を反転させる
	if (direction == Direction::LEFT) {
		int k = src.w;
		src.w = src.x;
		src.x = k;
	}
	this->playerimg.Draw(draw, src);
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Player::Finalize()
{
	std::cout << "Player解放" << std::endl;
	this->playerimg.Finalize();

}
//☆☆☆☆//-----------------------------------------------------------------------------
void Player::Register(CollisionManager* cm) {
	*cm += this;
	*cm += &(this->footBase);
	*cm += &(this->headBase);
	*cm += &(this->leftBase);
	*cm += &(this->rightBase);
}
//☆☆☆☆//-----------------------------------------------------------------------------
//関数
//☆☆☆☆//-----------------------------------------------------------------------------
//ジャンプの処理
void Player::JumpMove()
{
	//足判定trueの時は通常状態
	if (footBase.isCollided) {
		est.y = 0.f;
		//Zボタンを押したら、ジャンプ状態に移行する
		if (gameEngine->in.on(Input::B1,0)) {
			est.y = Player::JUMP_POWER;
		}
		//上昇中
		if (headBase.isCollided){
			est.y = 0.0f;	//上昇力を無効にする
		}
	}
}
//☆☆☆☆//-----------------------------------------------------------------------------
//足元接触判定
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
//☆☆☆☆//-----------------------------------------------------------------------------
//頭接触判定
void Player::CheckHead()
{
	headBase.CreateObject(Cube, Vec2(this->position.x, this->position.y + 1.f), Vec2(this->Scale.x, 1.f), 0.0f);
	headBase.objectTag = "PlayerHead";
	headBase.CollisionProcess = [&](const Object& o_) {
		//std::cout << o_.objectTag << std::endl;
		//当たり判定に通るか判断する
		if (isWalkable(o_.objectTag)) {
			//std::cout << "頭判定中" << std::endl;
			headBase.isCollided = true;
			this->est.y = 0.f;
		}
	};
}
//☆☆☆☆//-----------------------------------------------------------------------------
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
//☆☆☆☆//-----------------------------------------------------------------------------
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
//☆☆☆☆//-----------------------------------------------------------------------------
bool Player::isWalkable(std::string t) {
	for (auto& s : WALKABLE_CHIPS)
		if (t == s)
			return true;
	return false;
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Player::TakeBucket(Bucket* b_) {
	if (gameEngine->in.down(Input::B2, 0)) {
		if (bucket) {
			bucket = nullptr;
		}
		else if (this->hit(*b_)) {
			bucket = b_;
		}
	}
}