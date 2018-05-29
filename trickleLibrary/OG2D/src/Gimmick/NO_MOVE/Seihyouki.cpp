#include "Seihyouki.h"
using namespace std;

//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする
#include "Water\water.h"
bool Seihyouki::Initialize(Vec2& pos)
{
	//-----------------------------
	//生成時に処理する初期化処理を記述
	//-----------------------------
	this->taskName = "Seihyouki";	//検索時に使うための名を登録する
	__super::Init(taskName);		//TaskObject内の処理を行う

	movetime = 0;
	hitBace.CreateObject(Cube, pos, Vec2(64, 64), 0);
	this->GetFlag();
	cout << "製氷機　初期化" << endl;
	return true;
}
bool Seihyouki::Initialize(Vec2& pos ,std::shared_ptr<Switch> &target)
{
	//-----------------------------
	//生成時に処理する初期化処理を記述
	//-----------------------------
	this->taskName = "Seihyouki";	//検索時に使うための名を登録する
	__super::Init(taskName);		//TaskObject内の処理を行う

	movetime = 0;
	hitBace.CreateObject(Cube, pos, Vec2(64,64), 0);
	this->SetSwitchFlag(target);
	cout << "製氷機　初期化" << endl;
	return true;
}
void Seihyouki::GetFlag()
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
void Seihyouki::SetSwitchFlag(std::shared_ptr<Switch>&obj)
{
	if (obj != nullptr)
	{
		target = obj;
	}
}
bool Seihyouki::GetSwitchFlag()
{
	return switchflag;
}
void Seihyouki::UpDate()
{
	//--------------------
	//更新時に行う処理を記述
	//--------------------
	this->GetFlag();

	if (GetSwitchFlag())
	{
		toIce();
	}
}

void Seihyouki::Render2D()
{
	//--------------------
	//描画時に行う処理を記述
	//--------------------
}

bool Seihyouki::Finalize()
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
void Seihyouki::toIce()
{
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
	{
		if ((*id)->hit(hitBace))
		{
			if ((*id)->GetState() == Water::State::SOLID)
			{
				while (true)
				{
					movetime++;
					if (movetime >= movetime_ice)
					{
						(*id)->SetState(Water::State::LIQUID);
						movetime = 0;
						break;
					}
				}
			}
			if ((*id)->GetState() == Water::State::LIQUID)
			{
				while (true)
				{
					movetime++;
					if (movetime >= movetime_ice)
					{
						(*id)->SetState(Water::State::SOLID);
						movetime = 0;
						break;
					}
				}
			}
		}
	}
}
//----------------------------
//ここから下はclass名のみ変更する
//ほかは変更しないこと
//----------------------------
Seihyouki::Seihyouki()
{
	cout << "製氷機　生成" << endl;
}

Seihyouki::~Seihyouki()
{
	this->Finalize();
	cout << "製氷機　解放" << endl;
}
Seihyouki::SP Seihyouki::Create(Vec2& pos,bool flag_)
{
	Seihyouki::SP to = Seihyouki::SP(new Seihyouki());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}
Seihyouki::SP Seihyouki::Create(Vec2& pos,std::shared_ptr<Switch>&target,bool flag_)
{
	Seihyouki::SP to = Seihyouki::SP(new Seihyouki());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos , target))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}