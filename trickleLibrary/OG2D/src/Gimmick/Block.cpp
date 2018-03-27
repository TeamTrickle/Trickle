#include "Block.h"

using namespace std;

//ブロックギミック
//--------------------------------------------------------------------
//☆☆初期化☆☆
//--------------------------------------------------------------------
void GimmickB::Initialize()
{
	cout << "ブロックの初期化" << endl;
	this->BlockImg.TextureCreate(this->fileName);
	this->hitRight = false;
	this->hitLeft = false;
	this->hitbottom = true;
	this->speed = 0.0f;

	//ブロックオブジェクトの生成
	//position.x = 100;
	//position.y = 100;
	//Scale.x = 128.0f;
	//Scale.y = 128.0f;
	CreateObject(Cube, Vec2(100.0f,100.0f), Vec2(128.0f, 128.0f), 0.0f);

	//サイドの当たり判定用矩形
	HitR = Box2D(this->Scale.x, 0.0f, 1.0f, this->Scale.y);
	HitL = Box2D(-1.0f, 0.0f , 1.0f, this->Scale.y);
}

//----------------------------------------------------------------------
//☆☆更新☆☆
//----------------------------------------------------------------------
TaskFlag GimmickB::UpDate()
{
	TaskFlag nowtask = Block;

	//左に押したときの処理
	if (Input::KeyInputOn(Input::LEFT))
	{
		this->speed = -1.0f;
		if (hitRight == true)
		{
			this->position.x += this->speed;
		}
	}

	//右に押したときの処理
	if (Input::KeyInputOn(Input::RIGHT))
	{
		this->speed = 1.0f;
		if (hitLeft == true)
		{
			this->position.x += this->speed;
		}
	}

	//地面に接触していないときの処理
	if (hitbottom == false)
	{
		if (this->speed < 5.0f)
		{
			this->speed += 0.2f;
		}
		this->position.y += speed;
	}

	return nowtask;
}

//-----------------------------------------------------------------------------
//☆☆解放☆☆
//-----------------------------------------------------------------------------
void GimmickB::Finalize()
{
	cout << "ブロックの解放" << endl;
	this->BlockImg.Finalize();
}

//------------------------------------------------------------------------------
//☆☆描画☆☆
//------------------------------------------------------------------------------
void GimmickB::Render()
{
	//ブロック本体の描画
	{
		Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
		draw.OffsetSize();
		Box2D src(0, 0, 128, 128);
		this->BlockImg.Draw(draw, src);
	}

	//右側接触判定テスト用
	{
		Box2D draw(HitR.x, HitR.y, HitR.w, HitR.h);
		draw.Offset(this->position.x,this->position.y);
		draw.OffsetSize();

		Box2D src(0, 128, 128, 128);
		this->BlockImg.Draw(draw, src);
	}
	//左側接触判定テスト用
	{
		Box2D draw(HitL.x, HitL.y, HitL.w, HitL.h);
		draw.Offset(this->position.x, this->position.y);
		draw.OffsetSize();

		Box2D src(0, 128, 128, 128);
		this->BlockImg.Draw(draw, src);
	}
}
