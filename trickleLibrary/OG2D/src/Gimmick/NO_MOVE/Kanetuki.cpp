#include "Kanetuki.h"
using namespace std;

//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする
#include "Water\water.h"

bool Kanetuki::Initialize(Vec2& pos)
{
	//-----------------------------
	//生成時に処理する初期化処理を記述
	//-----------------------------
	this->taskName = "Kanetuki";	//検索時に使うための名を登録する
	__super::Init(taskName);		//Taskwaterect内の処理を行う

	Fire_movetime = 0;
	hitBace.CreateObject(Cube, pos, Vec2(64, 64), 0);
	this->GetFlag();
	cout << "加熱器　初期化" << endl;
	return true;
}
bool Kanetuki::Initialize(Vec2& pos,std::shared_ptr<Switch>& target)
{
	//-----------------------------
	//生成時に処理する初期化処理を記述
	//-----------------------------
	this->taskName = "Kanetuki";	//検索時に使うための名を登録する
	__super::Init(taskName);		//Taskwaterect内の処理を行う

	Fire_movetime = 0;
	hitBace.CreateObject(Cube, pos,Vec2(64,64), 0);
	this->SetSwitchFlag(target);

	cout << "加熱器　初期化" << endl;
	return true;
}
void Kanetuki::GetFlag()
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
void Kanetuki::UpDate()
{
	//--------------------
	//更新時に行う処理を記述
	//--------------------
	this->GetFlag();
	if (this->GetSwitchFlag())
	{
		this->toSteam();
	}
}

void Kanetuki::Render2D()
{
	//--------------------
	//描画時に行う処理を記述
	//--------------------
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
void Kanetuki::SetSwitchFlag(std::shared_ptr<Switch>& obj)
{
	if (obj != nullptr)
	{
		target = obj;
	}
}
bool Kanetuki::GetSwitchFlag()
{
	return switchflag;
}
void Kanetuki::toSteam()
{
	auto water = OGge->GetTasks<Water>("water");
	if (water != nullptr)
	{
		for (int i = 0; i < (*water).size(); ++i)
		{
			if ((*water)[i]->hit(hitBace))
			{
				if ((*water)[i]->GetState() == Water::State::SOLID)
				{
					while (true)
					{
						bool flag = false;
						Fire_movetime++;
						if (Fire_movetime >= Fire_time_SOLID)
						{
							(*water)[i]->SetState(Water::State::LIQUID);
							Fire_movetime = 0;
							flag = true;
						}
						if (flag)
						{
							break;
						}
					}
				}
				if ((*water)[i]->GetState() == Water::State::LIQUID)
				{
					while (true)
					{
						bool flag = false;
						Fire_movetime++;
						if (Fire_movetime >= Fire_time_LIQUID)
						{
							(*water)[i]->SetState(Water::State::GAS);
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
		}
	}
}
//----------------------------
//ここから下はclass名のみ変更する
//ほかは変更しないこと
//----------------------------
Kanetuki::Kanetuki()
{
	cout << "加熱器　生成" << endl;
}

Kanetuki::~Kanetuki()
{
	this->Finalize();
	cout << "加熱器　解放" << endl;
}

Kanetuki::SP Kanetuki::Create(Vec2& pos, bool flag_)
{
	Kanetuki::SP to = Kanetuki::SP(new Kanetuki());
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

Kanetuki::SP Kanetuki::Create(Vec2& pos,std::shared_ptr<Switch>& target,bool flag_)
{
	Kanetuki::SP to = Kanetuki::SP(new Kanetuki());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos,target))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}