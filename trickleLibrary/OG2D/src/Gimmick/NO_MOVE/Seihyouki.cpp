#include "Seihyouki.h"
using namespace std;

//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする

bool Seihyouki::Initialize()
{
	//-----------------------------
	//生成時に処理する初期化処理を記述
	//-----------------------------
	this->taskName = "";			//検索時に使うための名を登録する
	__super::Init(taskName);		//TaskObject内の処理を行う


	return true;
}
void Seihyouki::UpDate()
{
	//--------------------
	//更新時に行う処理を記述
	//--------------------
	for (auto& w : *water)
	{
		/*if (w->hit(hitBace))
		{
			toIce(w);
		}*/
	}
}

void Seihyouki::Render2D()
{
	//--------------------
	//描画時に行う処理を記述
	//--------------------
	Box2D draw(this->position, this->Scale);
	draw.OffsetSize();
	
}

bool Seihyouki::Finalize()
{
	//-----------------------------------------
	//このオブジェクトが消滅するときに行う処理を記述
	//-----------------------------------------
	this->sampleImage.Finalize();
	//次のタスクを作るかかつアプリケーションが終了予定かどうか
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		//自分を消す場合はKillを使う
		this->Kill();
	}
	return true;
}
void Seihyouki::toIce(Water* obj)
{
	if (obj->GetState() == Water::State::SOLID)
	{
		while (true)
		{
			movetime++;
			if (movetime >= movetime_ice)
			{
				obj->SetState(Water::State::LIQUID);
				movetime = 0;
				break;
			}
		}
	}
	if (obj->GetState() == Water::State::LIQUID)
	{
		while (true)
		{
			movetime++;
			if (movetime >= movetime_ice)
			{
				obj->SetState(Water::State::SOLID);
				movetime = 0;
				break;
			}
		}
	}
}
void Seihyouki::Create(Vec2 pos, Vec2 scale)
{
	movetime = 0;
	hitBace.CreateObject(Cube, pos, scale, 0);
}
void Seihyouki::SetWaterPool(std::vector<Water*>*w)
{
	water = w;
}
//----------------------------
//ここから下はclass名のみ変更する
//ほかは変更しないこと
//----------------------------
Seihyouki::Seihyouki()
{

}

Seihyouki::~Seihyouki()
{
	this->Finalize();
}

Seihyouki::SP Seihyouki::Create(bool flag_)
{
	Seihyouki::SP to = Seihyouki::SP(new Seihyouki());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize())
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}