#include "Player.h"

//☆☆☆☆//-----------------------------------------------------------------------------
void Player::Initialize()
{
	std::cout << "Player初期化" << std::endl;
	this->playerimg.TextureCreate(this->fileName);
	CreateObject(Cube, Vec2(10.0f, 700.0f), Vec2(128.0f, 128.0f), 0.0f);
	this->hitcheck = false;
	this->objectTag = "Player";
	//初期状態の向きを入れておく
	direction = Direction::RIGHT;
	//ジャンプ状態
	jumpFlag = false;

	//当たり判定
	Object::CollisionProcess = [&](const Object& o_) {
		if (o_.objectTag == "Floor") {
			std::cout << "床と当たり判定中！" << std::endl;
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
		/*playerimg.Draw.x = -playerimg.Draw.x;
		playerimg.Draw.w = -playerimg.Draw.w;*/
		//向きをLEFTに
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
	//trueの時はジャンプ状態、じゃなければ通常状態
	if (!jumpFlag) {
		est.y = 0.f;
		//Zボタンを押したら、ジャンプ状態に移行する
		if (Input::KeyInputOn(Input::Z)) {
			jumpFlag = true;
			est.y = Player::JUMP_POWER;
		}
	}
	//ジャンプ状態の処理
	else {
		//着地判定(未完成、MAPの当たり判定を実行したら)
		if (position.y >= 700) {
			jumpFlag = false;
		}
	}
}
//☆☆☆☆//-----------------------------------------------------------------------------
//足元接触判定
void CheckFoot()
{

}