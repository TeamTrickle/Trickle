#include "Block.h"

using namespace std;

//-------------------------------------------------------------------------
//統括
//-------------------------------------------------------------------------
void Block_::Initialize()
{
	cout << "ブロック初期化" << endl;
	pl_.Initialize();
	block_.Initialize();
}
TaskFlag Block_::UpDate()
{
	TaskFlag nowtask = Block;
	pl_.UpDate();
	block_.UpDate();
	//プレイヤとギミックの左右当たり判定
	Box2D plPos = Box2D(pl_.position.x, pl_.position.y, pl_.Scale.x, pl_.Scale.y);    //プレイヤの矩形を設定
	block_.HitCheckR(plPos);       //右側当たり判定
	block_.HitCheckL(plPos);       //左側当たり判定

	cout << "hitR_=" << block_.hitR_ << endl;
	cout << "hitL_=" << block_.hitL_ << endl;

	block_.hitCheck = block_.hit(pl_);         //当たり判定
	return nowtask;
}
void Block_::Finalize()
{
	cout << "ブロック解放" << endl;
	pl_.Finalize();
	block_.Finalize();
}
void Block_::Render()
{
	pl_.Render();
	block_.Render();
}

void Block1::Initialize()
{
	cout << "ブロックの初期化" << endl;
	this->BlockImg.TextureCreate(this->fileName);
	hitR_ = false;
	hitL_ = false;
	//position.x = 10;
	//position.y = 100;
	//Scale.x = 128.0f;
	//Scale.y = 128.0f;
	CreateObject(Cube, Vec2(200.0f, 300.0f), Vec2(128.0f, 128.0f), 0.0f);

	cout << "hitR=" << hitR.x << "," << hitR.y << "," << hitR.w << "," << hitR.h << endl;
	cout << "hitL=" << hitL.x << "," << hitL.y << "," << hitL.w << "," << hitL.h << endl;

	this->hitCheck = false;
}
void Block1::UpDate()
{
	if (hitR_)
	{
		speed = -1.0f;
		if (Input::KeyInputOn(Input::LEFT))
		{
			position.x += speed;
		}
	}
	if (hitL_)
	{
		speed = 1.0f;
		if (Input::KeyInputOn(Input::RIGHT))
		{
			position.x += speed;
		}
	}
	hitR = Box2D(position.x + Scale.x, position.y, 1.0f, Scale.y);
	hitL = Box2D(position.x - 1.0f, position.y, 1.0f, Scale.y);

	if (hitCheck)
	{
		cout << "当たったブロック" << endl;
	}
}
void Block1::Finalize()
{
	cout << "ブロックの開放" << endl;
	this->BlockImg.Finalize();
}
void Block1::Render()
{
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src(0, 0, 128, 128);
	if (hitCheck)
	{
		src.y += 128;
		src.OffsetSize();
	}
	this->BlockImg.Draw(draw, src);
}

void Block1::HitCheckR(Box2D p_)
{
	hitR_ = false;
	if (hitR.x < p_.x+p_.w)
	{
		if (hitR.x+hitR.w > p_.x)
		{
			if (hitR.y < p_.y+p_.h)
			{
				if (hitR.y+hitR.h > p_.y)
				{
					hitR_ = true;
				}
			}
		}
	}
}
void Block1::HitCheckL(Box2D p_)
{
	hitL_ = false;
	if (hitL.x < p_.x + p_.w)
	{
		if (hitL.x + hitL.w > p_.x)
		{
			if (hitL.y < p_.y + p_.h)
			{
				if (hitL.y + hitL.h > p_.y)
				{
					hitL_ = true;
				}
			}
		}
	}
}

//---------------------------------------------------------------------------------
//プレイヤー仮
//---------------------------------------------------------------------------------
void Player1::Initialize()
{
	cout << "プレイヤ仮の初期化" << endl;
	this->PlImg.TextureCreate(this->fileName);
	//position.x = 10;
	//position.y = 100;
	//Scale.x = 128.0f;
	//Scale.y = 128.0f;
	CreateObject(Cube, Vec2(50.0f, 400.0f), Vec2(128.0f, 128.0f), 0.0f);
	this->hitCheck = false;
}
void Player1::UpDate()
{
	if (Input::KeyInputOn(Input::UP))
	{
		this->position.y += 1.0f;
	}
	if (Input::KeyInputOn(Input::DOWN))
	{
		this->position.y -= 1.0f;
	}
	if (Input::KeyInputOn(Input::RIGHT))
	{
		this->position.x += 1.0f;
	}
	if (Input::KeyInputOn(Input::LEFT))
	{
		this->position.x -= 1.0f;
	}
	if (Input::KeyInputOn(Input::Q))
	{
		this->angle -= 1.0f;
	}
	if (Input::KeyInputOn(Input::E))
	{
		this->angle += 1.0f;
	}
}
void Player1::Finalize()
{
	cout << "プレイヤ仮の開放" << endl;
	this->PlImg.Finalize();
}
void Player1::Render()
{
	cout << "playerPosition=" << position.x << "," << position.y << "," << Scale.x << "," << Scale.y << endl;

	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src(0, 0, 128, 128);
	if (hitCheck)
	{
		src.y += 128;
		src.OffsetSize();
	}
	this->PlImg.Draw(draw, src);
}