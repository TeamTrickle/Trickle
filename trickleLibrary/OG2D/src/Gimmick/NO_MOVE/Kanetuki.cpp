#include "Kanetuki.h"
using namespace std;

//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする
#include "Water\water.h"

bool Kanetuki::Initialize(Vec2& pos , Vec2& scale)
{
	//-----------------------------
	//生成時に処理する初期化処理を記述
	//-----------------------------
	this->taskName = "Kanetuki";			//検索時に使うための名を登録する
	__super::Init(taskName);		//Taskwaterect内の処理を行う

	Set_Pos(pos, scale);

	return true;
}
void Kanetuki::UpDate()
{
	//--------------------
	//更新時に行う処理を記述
	//--------------------
	auto water = OGge->GetTask<Water>("Water");
	if (water->hit(hitBace))
	{
		toSteam();
	}
}

void Kanetuki::Render2D()
{
	//--------------------
	//描画時に行う処理を記述
	//--------------------
	Box2D draw(this->position, this->Scale);
	draw.OffsetSize();
	
}

bool Kanetuki::Finalize()
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
void Kanetuki::HitGeneration(Vec2& pos , Vec2& scale)
{
	Fire_movetime = 0;
	hitBace.CreateObject(Cube, pos, scale, 0);
}

//void Kanetuki::SetWaterPool(std::vector<Water*>* w)
//{
//	water = w;
//}
void Kanetuki::toSteam()
{
	auto water = OGge->GetTask<Water>("Water");

	if (water->GetState() == Water::State::SOLID)
	{
		while (true)
		{
			bool flag = false;
			Fire_movetime++;
			if (Fire_movetime >= Fire_time_SOLID)
			{
				water->SetState(Water::State::LIQUID);
				Fire_movetime = 0;
				flag = true;
			}
			if (flag)
			{
				break;
			}
		}
	}
	if (water->GetState() == Water::State::LIQUID)
	{
		while (true)
		{
			bool flag = false;
			Fire_movetime++;
			if (Fire_movetime >= Fire_time_LIQUID)
			{
				water->SetState(Water::State::GAS);
				Fire_movetime = 0;
				flag = true;
			}
			if (flag)
			{
				break;
			}
		}
	}
}
//----------------------------
//ここから下はclass名のみ変更する
//ほかは変更しないこと
//----------------------------
Kanetuki::Kanetuki()
{

}

Kanetuki::~Kanetuki()
{
	this->Finalize();
}

Kanetuki::SP Kanetuki::Create(Vec2& pos, Vec2& scale,bool flag_)
{
	Kanetuki::SP to = Kanetuki::SP(new Kanetuki());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos ,scale))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}