#include "Senpuki.h"
using namespace std;

//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする
#include "Gimmick\NO_MOVE\Switch.h"
#include "Water\water.h"
bool Fan::Initialize(Vec2 pos, float r, Fan::Dir d, bool activ)
{
	//-----------------------------
	//生成時に処理する初期化処理を記述
	//-----------------------------
	this->taskName = "Senpuki";			//検索時に使うための名を登録する
	__super::Init(taskName);		//TaskObject内の処理を行う

	position = pos;
	objectTag = "Fan";
	range = r;
	dir = d;
	active = activ;
	if (dir == Fan::Dir::LEFT)
	{
		CreateObject(Cube, pos, Vec2(64.0f, 64.0f), 0.0f);
		strength = -3;
		this->WindHitBase.CreateObject(Cube, Vec2(pos.x - (64 * 8), pos.y), Vec2(64 * 8, 64), 0.0f);
	}
	else
	{
		CreateObject(Cube, pos, Vec2(64.0f, 64.0f), 0.0f);
		strength = 3;
		this->WindHitBase.CreateObject(Cube, pos, Vec2(64 * 16, 64), 0.0f);
		//this->WindHitBase.CreateObject(Cube, Vec2(0,0), Vec2(0,0), 0.0f);
	}

	std::cout << "扇風機　初期化" << std::endl;
	return true;
}
void Fan::UpDate()
{
	//--------------------
	//更新時に行う処理を記述
	//--------------------
	auto waters = OGge->GetTasks<Water>("Water");
	if (waters)
	{
		for (int i = 0; i < (*waters).size(); ++i)
		{
			if ((*waters)[i]->hit(WindHitBase))
			{
				Motion();
			}
		}
	}
}

void Fan::Render2D()
{
	//--------------------
	//描画時に行う処理を記述
	//--------------------
	Box2D draw(this->position, this->Scale);
	draw.OffsetSize();
	Box2D src(0, 0, 256, 256);
	if (this->dir == Fan::Dir::LEFT)
	{
		int k = src.w;
		src.w = src.x;
		src.x = k;
	}
	this->image->Draw(draw, src);
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
void Fan::SetTexture(Texture* tex)
{
	this->image = tex;
}
//void Fan::SetWaterPool(Water* w)
//{
//	this->water.push_back(w);
//}
//bool Fan::DeleteWaterPool(Water* w)
//{
//	for (auto id = this->water.begin(); id != this->water.end(); ++id)
//	{
//		if ((*id) == w)
//		{
//			this->water.erase(id);
//			return true;
//		}
//	}
//	return false;
//}
void Fan::SetWindRange(Vec2& b)
{
	this->WindHitBase.Scale = b;
}
void Fan::AddSwitch(Switch* swit)
{
	switches.push_back(swit);
}
void Fan::ChangeState()
{
	active = !active;
}
void Fan::Motion()
{
	auto water = OGge->GetTask<Water>("Water");
	if (water)
	{
		if (active)
		{
			if (water->GetState() == Water::State::GAS)
			{
				water->MovePos(Vec2(strength, 0));
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

Fan::SP Fan::Create(Vec2 pos, float r, Fan::Dir d, bool activ, bool flag_)
{
	Fan::SP to = Fan::SP(new Fan());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos,r,d,activ))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}
