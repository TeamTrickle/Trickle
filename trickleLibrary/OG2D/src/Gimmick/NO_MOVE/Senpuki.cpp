#include "Senpuki.h"
using namespace std;

//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする
#include "Gimmick\NO_MOVE\Switch.h"
#include "Water\water.h"
bool Fan::Initialize(Vec2 pos, float r, Fan::Dir d)
{
	//-----------------------------
	//生成時に処理する初期化処理を記述
	//-----------------------------
	this->taskName = "Senpuki";			//検索時に使うための名を登録する
	__super::Init(taskName);		//TaskObject内の処理を行う

	range = r;
	dir = d;
	//扇風機の描画座標
	position = pos;
	if (dir == Fan::Dir::LEFT)
	{
		strength = -3;
		this->WindHitBase.CreateObject(Cube, Vec2(position.x - (64.f * r), position.y), Vec2(64.f * r + pos.x - (pos.x - 64), 64.f), 0.0f);
	}
	else
	{
		strength = 3;
		this->WindHitBase.CreateObject(Cube, pos, Vec2(64 * r, 64.f), 0.0f);
	}
	animetion.AnimetionReset();

	this->GetFlag();
	std::string filePath = "fan.png";
	image.Create(filePath);
	std::cout << "扇風機　初期化" << std::endl;
	return true;
}
bool Fan::Initialize(Vec2 pos, float r, Fan::Dir d,std::shared_ptr<Switch>&obj)
{
	//-----------------------------
	//生成時に処理する初期化処理を記述
	//-----------------------------
	this->taskName = "Senpuki";			//検索時に使うための名を登録する
	__super::Init(taskName);		//TaskObject内の処理を行う

	//扇風機の描画座標
	position = pos;
	dir = d;
	range = r;

	if (dir == Fan::Dir::LEFT)
	{
		strength = -3;
		this->WindHitBase.CreateObject(Cube, Vec2(position.x - (64.f * r), position.y), Vec2(64.f * r + pos.x, 64.f), 0.0f);
	}
	else
	{
		strength = 3;
		this->WindHitBase.CreateObject(Cube, pos, Vec2(64 * r, 64.f), 0.0f);
	}
	animetion.AnimetionReset();

	this->SetSwitchFlag(obj);
	std::string filePath = "fan.png";
	image.Create(filePath);
	std::cout << "扇風機　初期化" << std::endl;
	return true;
}
void Fan::Animetion::AnimetionReset()
{
	this->animetionframe = 0;
	this->speed = 0;
}
void Fan::GetFlag()
{
	if (target != nullptr)
	{
		switchflag = target->GetisON();
	}
	else
	{
		switchflag = true;
	}
}
void Fan::SetSwitchFlag(std::shared_ptr<Switch>&obj)
{
	if (obj != nullptr)
	{
		this->target = obj;
	}
}
bool Fan::GetSwitchFlag()
{
	return switchflag;
}
void Fan::Animetion::AnimetionMove(bool flag)
{
	this->speed = 2;
	//扇風機が稼働している
	if (flag)
	{
		if (animetionframe <= 300)
		{
			animetionframe++;
		}
		else
		{
			animetionframe += speed;
		}
	}
	else
	{
		if (animetionframe >= 300)
		{
			animetionframe -= 10;
		}
		else if(animetionframe > 0)
		{
			animetionframe -= speed;
		}
		else
		{
			this->AnimetionReset();
		}
	}
}
void Fan::UpDate()
{
	//--------------------
	//更新時に行う処理を記述
	//--------------------
	this->GetFlag();
	if (GetSwitchFlag())
	{
		animetion.AnimetionMove(GetSwitchFlag());
		Motion();
	}
	else
	{
		animetion.AnimetionMove(GetSwitchFlag());
		animetion.AnimetionReset();
	}
}
void Fan::Animetion::AnimetionSrc(Box2D& src, bool flag)
{
	if (flag)
	{
		//アニメーションの計算をする
		if (animetionframe <= 120)
		{
			src.x += (animetionframe / 15 % 3)* src.w;
		}
		else if (animetionframe <= 160)
		{
			src.x += (animetionframe / 8 % 3)* src.w;
		}
		else
		{
			src.x += (animetionframe / 5 % 3)* src.w;
		}
	}
	else
	{
		//アニメーションの計算をする
		if (animetionframe >= 160)
		{
			src.x += (animetionframe / 15 % 3)* src.w;
		}
		else if (animetionframe >= 120)
		{
			src.x += (animetionframe / 8 % 3)* src.w;
		}
		else
		{
			src.x += (animetionframe / 5 % 3)* src.w;
		}
	}
}
void Fan::Render2D()
{
	//--------------------
	//描画時に行う処理を記述
	//--------------------
	Box2D draw(position, Vec2(64, 64));
	draw.OffsetSize();
	Box2D src = this->Src;
	this->animetion.AnimetionSrc(src,GetSwitchFlag());
	src.OffsetSize();
	if (this->dir == Fan::Dir::LEFT)
	{
		int k = src.w;
		src.w = src.x;
		src.x = k;
	}
	
	this->image.Draw(draw, src);
}

bool Fan::Finalize()
{
	//-----------------------------------------
	//このオブジェクトが消滅するときに行う処理を記述
	//-----------------------------------------

	//次のタスクを作るかかつアプリケーションが終了予定かどうか
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		
	}
	return true;
}
void Fan::SetWindRange(Vec2& b)
{
	this->WindHitBase.Scale = b;
}
void Fan::Motion()
{
	auto water = OGge->GetTasks<Water>("water");
	if (water)
	{
		for (auto id = (*water).begin(); id != (*water).end(); ++id)
		{
			if ((*id)->hit(this->WindHitBase))
			{
				if ((*id)->GetState() == Water::State::GAS)
				{
					(*id)->MovePos(Vec2(this->strength, 0));
				}
			}
		}
	}
}
//----------------------------
//ここから下はclass名のみ変更する
//ほかは変更しないこと
//----------------------------
Fan::Fan()
{
	std::cout << "扇風機　生成" << std::endl;
}
Fan::~Fan()
{
	this->Finalize();
	std::cout << "扇風機　解放" << std::endl;
}
Fan::SP Fan::Create(Vec2 pos, float r, Fan::Dir d, bool flag_)
{
	Fan::SP to = Fan::SP(new Fan());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos, r, d))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}

Fan::SP Fan::Create(Vec2 pos, float r, Fan::Dir d,std::shared_ptr<Switch>&target, bool flag_)
{
	Fan::SP to = Fan::SP(new Fan());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos,r,d,target))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}
