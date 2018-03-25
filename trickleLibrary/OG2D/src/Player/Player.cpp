#include "Player.h"


void Player::Initialize()
{
	std::cout << "Player初期化" << std::endl;
	this->playerimg.TextureCreate(this->fileName);
	CreateObject(Cube, Vec2(10.0f, 600.0f), Vec2(128.0f, 128.0f), 0.0f);
	this->hitcheck = false;

	//ジャンプ状態
	jumpFlag = false;
	//移動スピード
	speed = 0.15f;
}

void Player::UpDate()
{
	Vec2 est;
	//if (Input::KeyInputOn(Input::LEFT)) {
	//	est.x -= 1;
	//}
	//if (Input::KeyInputOn(Input::RIGHT)) {
	//	est.x += 1;
	//}
	//if (Input::KeyInputOn(Input::UP)) {
	//	est.y -= 1;
	//}
	//if (Input::KeyInputOn(Input::DOWN)) {
	//	est.y += 1;
	//}
	position.y += 1;

	//ジャンプの処理
	JumpMove(est);



	est.Normalize();
	//est *= speed;
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
void Player::JumpMove(Vec2& e_)
{
	e_.x = 0;
	if (Input::KeyInputOn(Input::LEFT)) {
		e_.x = -speed;
	}
	if (Input::KeyInputOn(Input::RIGHT)) {
		e_.x = speed;
	}

	//trueの時はジャンプ状態、じゃなければ通常状態
	if (!jumpFlag) {
		//Zボタンを押したら、ジャンプ状態に移行する
		if (Input::KeyInputOn(Input::Z)) {
			jumpFlag = true;
			e_.y = Player::JUMP_POWER;
		}
	}
	//ジャンプ状態の処理
	else {
		//y方向の速度に加速度を加える
		e_.y += Player::GRAVITY;
		//y座標の更新
		position.y += e_.y;
		//着地判定(未完成、MAPの当たり判定を実行したら)
		if (e_.y>0 /*&& position.y >= ground_y*/) {
			jumpFlag = false;
			e_.y = 0.f;
		}
	}
}