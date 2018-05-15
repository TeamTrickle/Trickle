#include "Seihyouki.h"
using namespace std;

//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする
#include "Water\water.h"
bool Seihyouki::Initialize(Vec2& pos , Vec2& scale)
{
	//-----------------------------
	//生成時に処理する初期化処理を記述
	//-----------------------------
	this->taskName = "Seihyouki";			//検索時に使うための名を登録する
	__super::Init(taskName);		//TaskObject内の処理を行う

	HitGeneration(pos,scale);

	return true;
}
void Seihyouki::UpDate()
{
	//--------------------
	//更新時に行う処理を記述
	//--------------------
	auto water = OGge->GetTask<Water>("Water");
	if (water->hit(hitBace))
	{
		toIce();
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
		
	}
	return true;
}
void Seihyouki::toIce()
{
	auto water = OGge->GetTask<Water>("Water");
	if (water->GetState() == Water::State::SOLID)
	{
		while (true)
		{
			movetime++;
			if (movetime >= movetime_ice)
			{
				water->SetState(Water::State::LIQUID);
				movetime = 0;
				break;
			}
		}
	}
	if (water->GetState() == Water::State::LIQUID)
	{
		while (true)
		{
			movetime++;
			if (movetime >= movetime_ice)
			{
				water->SetState(Water::State::SOLID);
				movetime = 0;
				break;
			}
		}
	}
}
void Seihyouki::HitGeneration(Vec2& pos, Vec2& scale)
{
	movetime = 0;
	hitBace.CreateObject(Cube, pos, scale, 0);
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

Seihyouki::SP Seihyouki::Create(Vec2& pos,Vec2& scale,bool flag_)
{
	Seihyouki::SP to = Seihyouki::SP(new Seihyouki());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos , scale))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}