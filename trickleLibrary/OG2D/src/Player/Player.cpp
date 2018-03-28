#include "Player.h"

//☆☆☆☆//-----------------------------------------------------------------------------
void Player::Initialize()
{
	std::cout << "Player初期化" << std::endl;
	this->playerimg.TextureCreate(this->fileName);
	CreateObject(Cube, Vec2(10.0f, 200.0f), Vec2(64.0f, 64.0f), 0.0f);
	
	
	//足判定用
	footBase.CreateObject(Cube, Vec2(this->position.x, this->position.y + this->Scale.y), Vec2(this->Scale.x, 1.0f), 0.0f);
	footBase.objectTag = "PlayerFoot";
	footBase.CollisionProcess = [&](const Object& o_) {
		std::cout << o_.objectTag << std::endl;
		if (o_.objectTag == "Floor") {
			std::cout << "足元判定中" << std::endl;		//表せない？？？
			footBase.isCollided = true;
			/*jumpFlag = false;*/
		}
	};


	this->hitcheck = false;
	this->objectTag = "Player";
	//当たり判定初期化
	this->isCollided = false;
	//初期状態の向きを入れておく
	direction = Direction::RIGHT;
	//ジャンプ状態
	jumpFlag = false;

	//当たり判定
	Object::CollisionProcess = [&](const Object& o_) {
		if (o_.objectTag == "Floor") {
			/*std::cout << "床と当たり判定中！" << std::endl;*/
			this->isCollided = true;
			jumpFlag = false;
		}
	};
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Player::UpDate()
{
	//キャラクターの移動処理
	est.x = 0;
	if (Input::KeyInputOn(Input::LEFT)) {
		est.x = -Player::MOVE_SPEED;
		//キャラクターの向き変換
		direction = Direction::LEFT;
	}
	if (Input::KeyInputOn(Input::RIGHT)) {
		est.x = Player::MOVE_SPEED;
		//向きをRIGHTに
		direction = Direction::RIGHT;
	}

	//y方向の速度に加速度を加える
	est.y += Player::GRAVITY;

	//ジャンプの処理
	JumpMove();
	//足元接触判定
	//CheckFoot();

	position += est;
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
//関数
//☆☆☆☆//-----------------------------------------------------------------------------
//ジャンプの処理
void Player::JumpMove()
{
	footBase.position = Vec2(this->position.x, this->position.y + this->Scale.y);
	//trueの時はジャンプ状態、じゃなければ通常状態
	if (footBase.isCollided) {
		est.y = 0.f;
		//Zボタンを押したら、ジャンプ状態に移行する
		if (Input::KeyInputOn(Input::Z)) {
			est.y = Player::JUMP_POWER;
		}
	}
}
//☆☆☆☆//-----------------------------------------------------------------------------
//足元接触判定
void Player::CheckFoot()
{
	footBase.CreateObject(Cube, Vec2(this->position.x, this->position.y + this->Scale.y), Vec2(this->Scale.x, 1.0f), 0.0f);
	footBase.objectTag = "PlayerFoot";
	footBase.CollisionProcess = [&](const Object& o_) {
		std::cout << "足元判定中" << std::endl;
		this->isCollided = true;
	};
}