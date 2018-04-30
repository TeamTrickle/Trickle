#include "Container.h"

using namespace std;


//-------------------------------------------------------------------------
//統括
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//統括☆初期化
//--------------------------------------------------------------------------
void Container_::Initialize()
{
	cout << "容器初期化" << endl;
	//pl_.Initialize();
	youki_.Initialize();
}
//--------------------------------------------------------------------------
//統括☆更新
//--------------------------------------------------------------------------
void Container_::UpDate()
{
	//TaskFlag nowtask = Container;
	//pl_.UpDate();
	youki_.UpDate();

	//youki_.hitCheck = youki_.hit(pl_);         //当たり判定

	//プレイヤが容器をを持った場合の座標設定
	if (youki_.hold)
	{
		/*youki_.position.x = pl_.position.x + 20;
		youki_.position.y = pl_.position.y + 30;*/
	}

	//return nowtask;
}

//----------------------------------------------------------------------------
//統括☆解放
//----------------------------------------------------------------------------
void Container_::Finalize()
{
	cout << "容器解放" << endl;
	//pl_.Finalize();
	youki_.Finalize();
}
//----------------------------------------------------------------------------
//統括☆描画
//----------------------------------------------------------------------------
void Container_::Render()
{
	//pl_.Render();
	youki_.Render();
}

//-------------------------------------------------------------------------------
//容器
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//容器☆初期化
//-------------------------------------------------------------------------------
void Youki::Initialize()
{
	cout << "容器の初期化" << endl;
	this->water = 0.0f;         //初期値として水は入っていない
	this->ContainerImg.TextureCreate(this->fileName);
	this->hold = false;
	//position.x = 10;
	//position.y = 100;
	//Scale.x = 128.0f;
	//Scale.y = 128.0f;
	//CreateObject(Cube, Vec2(200.0f, 300.0f), Vec2(128.0f, 128.0f), 0.0f);
	
	//関数テスト用
	Box2D pos=Box2D(200.0f,300.0f,128.0f,128.0f);
	CreateNew(pos);

	this->hitCheck = false;
}
//--------------------------------------------------------------------------------------
//容器☆更新
//--------------------------------------------------------------------------------------
//TaskFlag Youki::UpDate()
void Youki::UpDate()
{
	//-------------------------------------------------------------------------------
	//容器を持つ処理
	//-------------------------------------------------------------------------------
	if (this->hold == false)           //プレイヤが容器を持っていない
	{
		if (this->hitCheck)            //プレイヤが容器を持てる場所に居る
		{
			//if (Input::KeyInputDown(Input::S))
			if(gameEngine->in.down(In::S))
			{
				this->hold = true;
			}
		}
	}
	//---------------------------------------------------------------------------------
	//容器を離す処理
	//---------------------------------------------------------------------------------
	if (this->hold == true)
	{
		//if (Input::KeyInputDown(Input::S))
		if(gameEngine->in.down(In::S))
		{
			this->hold = false;
		}
	}
}
//------------------------------------------------------------------------------
//容器☆解放
//------------------------------------------------------------------------------
void Youki::Finalize()
{
	cout << "容器の開放" << endl;
	this->ContainerImg.Finalize();
}
//------------------------------------------------------------------------------
//容器☆描画
//------------------------------------------------------------------------------
void Youki::Render()
{
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src(0, 0, 128, 128);
	if (hitCheck)
	{
		src.y += 128;
		src.OffsetSize();
	}
	this->ContainerImg.Draw(draw, src);
}

void Youki::CreateNew(Box2D pos)
{
	cout << "生成" << endl;
	CreateObject(Cube, Vec2(pos.x, pos.y), Vec2(pos.w, pos.h), 0.0f);
}


//---------------------------------------------------------------------------------
//プレイヤーテスト用
//---------------------------------------------------------------------------------
//void Player::Initialize()
//{
//	cout << "プレイヤ仮の初期化" << endl;
//	this->PlImg.TextureCreate(this->fileName);
//	//position.x = 10;
//	//position.y = 100;
//	//Scale.x = 128.0f;
//	//Scale.y = 128.0f;
//	CreateObject(Cube, Vec2(200.0f, 400.0f), Vec2(128.0f, 128.0f), 0.0f);
//	this->hitCheck = false;
//}
//void Player::UpDate()
//{
//	//if (Input::KeyInputOn(Input::UP))
//	if(gameEngine->in.down(In::UP))
//	{
//		this->position.y += 1.0f;
//	}
//	//if (Input::KeyInputOn(Input::DOWN))
//	if(gameEngine->in.down(In::DOWN))
//	{
//		this->position.y -= 1.0f;
//	}
//	//if (Input::KeyInputOn(Input::RIGHT))
//	if(gameEngine->in.down(In::RIGHT))
//	{
//		this->position.x += 1.0f;
//	}
//	//if (Input::KeyInputOn(Input::LEFT))
//	if(gameEngine->in.down(In::LEFT))
//	{
//		this->position.x -= 1.0f;
//	}
//	//if (Input::KeyInputOn(Input::Q))
//	if(gameEngine->in.down(In::Q))
//	{
//		this->angle -= 1.0f;
//	}
//	//if (Input::KeyInputOn(Input::E))
//	if(gameEngine->in.down(In::E))
//	{
//		this->angle += 1.0f;
//	}
//}
//void Player::Finalize()
//{
//	cout << "プレイヤ仮の開放" << endl;
//	this->PlImg.Finalize();
//}
//void Player::Render()
//{
//	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
//	draw.OffsetSize();
//	Box2D src(0, 0, 128, 128);
//	if (hitCheck)
//	{
//		src.y += 128;
//		src.OffsetSize();
//	}
//	this->PlImg.Draw(draw, src);
//}