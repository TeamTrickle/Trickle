#include "Player.h"


void Player::Initialize()
{
	std::cout << "Player初期化" << std::endl;
	this->playerimg.TextureCreate(this->fileName);
	CreateObject(Cube, Vec2(10.0f, 300.0f), Vec2(128.0f, 128.0f), 0.0f);
	this->hitcheck = false;

	//ジャンプ状態
	jumpFlag = false;
}

void Player::UpDate()
{
	est.x = 0;
	if (Input::KeyInputOn(Input::LEFT)) {
		est.x = -Player::MOVE_SPEED;
	}
	if (Input::KeyInputOn(Input::RIGHT)) {
		est.x = Player::MOVE_SPEED;
	}

	//y方向の速度に加速度を加える
	est.y += Player::GRAVITY;

	//ジャンプの処理
	JumpMove();
	position += est;
}

void Player::Render()
{
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src(0, 0, 128, 128);
	this->playerimg.Draw(draw, src);
}

void Player::Finalize()
{
	std::cout << "Player解放" << std::endl;
	this->playerimg.Finalize();

}
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