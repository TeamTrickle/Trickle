#include "WeightSwitch.h"

//当たり判定をする必要のあるファイルの読み込み
#include "Block/block.h"
#include "Bucket/bucket.h"
#include "Water/water.h"
#include "Player/Player.h"

WeightSwitch::WeightSwitch(const Vec2& pos_, const Vec2& size_, const float mass_)     //座標、大きさ、必要な重さ
{
	std::cout << "スイッチ生成" << std::endl;
	this->objectTag = "WeightSwitch";
	this->taskName = "WeightSwitch";
	__super::Init(this->objectTag);
	__super::SetDrawOrder(0.5f);              //描画順を設定
	auto WSwitch = OGge->GetTasks<WeightSwitch>(this->objectTag);

	CreateObject(Cube, pos_, size_);         //オブジェクトを生成
	this->maxmass = mass_;                   //扉が開く重さを格納
	this->totalmass = 0.0f;                  //乗っているものの総合の重さ格納
	this->nowActive = false;                 //今扉が開けるか
	this->premass = 0.0f;
	//今そのオブジェクトと当たり判定をしてよいか
	this->canPlhitCheck = true;         //プレイヤ
	this->canBlockhitCheck = true;      //ブロック
	this->canIcehitCheck = true;        //氷
	this->canBuckethitCheck = true;     //バケツ
}
WeightSwitch::~WeightSwitch()
{
	std::cout << "スイッチを消去" << std::endl;
	this->image = nullptr;
}


void WeightSwitch::UpDate()
{
	this->Getmass();
	//扉の駆動について
	if (this->totalmass >= this->maxmass)      //扉が開く重さになった
	{
		this->nowActive = true;
	}
	else                                      //まだ軽い
	{
		this->nowActive = false;
	}
}
void WeightSwitch::Render2D()
{
	//状態によって描画画像を変える　未実装
	//if (state == Nomal)
	//{

	//}
	//if (state == Riding)
	//{

	//}

	//スイッチの描画
	this->draw = Box2D(this->position, this->Scale);
	draw.OffsetSize();
	this->src = Box2D(0, 0, 128, 128);
	src.OffsetSize();
	this->image->Draw(draw, src);
	this->LineDraw();
}

//当たっているオブジェクトの重さを取得
void WeightSwitch::Getmass()
{
	std::cout <<"現在の重さ"<< totalmass << std::endl;
	//氷の重さの取得---------------------------------------------------------
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
	{
		//水との当たり判定
		if ((*id)->GetState() == Water::State::SOLID)
		{
			if ((*id)->CubeHit(*this))
			{
				if (canIcehitCheck == true)
				{
					premass = totalmass;            //加算する前の重さを格納
					this->totalmass += (*id)->mass;
					canIcehitCheck = false;
					//デバッグ用
					//std::cout << this->totalmass << std::endl;
				}
			}
			else
			{
				if(canIcehitCheck==false)
				{
					canIcehitCheck = true;                    //変数をオブジェクトごとに変えたほうがいいかも
					//this->totalmass = premass;          //外に出たら重さを元に戻す
					this->totalmass -= (*id)->mass;
					//デバッグ用
					//std::cout << this->totalmass << std::endl;
				}
			}
		}
	}
	//バケツの重さ取得-----------------------------------------------------
	auto buckets = OGge->GetTasks<Bucket>("bucket");
	for (auto id = (*buckets).begin(); id != (*buckets).end(); ++id)
	{
		//バケツとの当たり判定
		if ((*id)->CubeHit(*this))
		{
			if (canBuckethitCheck == true)
			{
				premass = totalmass;            //加算する前の重さを格納
				this->totalmass += (*id)->mass;
				canBuckethitCheck = false;
				//デバッグ用
				//std::cout << this->totalmass << std::endl;
			}
		}
		else
		{
			if (canBuckethitCheck == false)
			{
				canBuckethitCheck = true;
				this->totalmass = premass;          //外に出たら重さを元に戻す
				//デバッグ用
				//std::cout << this->totalmass << std::endl;
			}
		}
	}
	//ブロックの重さ取得--------------------------------------------------------
	auto blocks = OGge->GetTasks<Block>("block");
	for (auto id = (*blocks).begin(); id != (*blocks).end(); ++id)
	{
		//ブロックとの当たり判定
		if ((*id)->CubeHit(*this))
		{
			if (canBlockhitCheck == true)
			{
				premass = totalmass;            //加算する前の重さを格納
				this->totalmass += (*id)->mass;
				canBlockhitCheck = false;
				//デバッグ用
				//std::cout << this->totalmass << std::endl;
			}
		}
		else
		{
			if (canBlockhitCheck == false)
			{
				canBlockhitCheck = true;
				this->totalmass = premass;          //外に出たら重さを元に戻す
				//デバッグ用
				//std::cout << this->totalmass << std::endl;
			}
		}
	}
	//プレイヤの重さ取得---------------------------------------------------------
	auto player = OGge->GetTask<Player>("Player");
	//プレイヤとの当たり判定
	if (player->CubeHit(*this))
	{
		if (canPlhitCheck == true)
		{
			premass = totalmass;            //加算する前の重さを格納
			this->totalmass += player->mass;
			canPlhitCheck = false;
			//デバッグ用
			//std::cout << this->totalmass << std::endl;
		}
	}
	else
	{
		if (canPlhitCheck == false)
		{
			this->canPlhitCheck = true;
			//this->totalmass = premass;          //外に出たら重さを元に戻す
			this->totalmass -= player->mass;
			//デバッグ用
			//std::cout << this->totalmass << std::endl;
		}
	}
}

//現在のスイッチの状態を返す (扉を開けるのに使用)
bool WeightSwitch::SetnowState()
{
	return nowActive;     //スイッチの今の状態を返す
}

//画像を設定する
void WeightSwitch::SetTexture(Texture* tex)
{
	this->image = tex;
}

//スイッチの生成について
WeightSwitch::SP WeightSwitch::Create(const Vec2& pos, const Vec2& size, const float mass)
{
	WeightSwitch::SP to = WeightSwitch::SP(new WeightSwitch(pos, size, mass));
	if (to)
	{
		to->me = to;
		OGge->SetTaskObject(to);
		return to;
	}
	return nullptr;
}