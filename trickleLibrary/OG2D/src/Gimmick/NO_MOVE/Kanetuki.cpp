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

	Fire_MovetimeReset();
	CreateObject(Cube, pos, Vec2(64, 64), 0);
	this->GetFlag();
	cout << "加熱器　初期化" << endl;
	return true;
}
bool Kanetuki::Initialize(Vec2& pos, std::shared_ptr<Switch>& target)
{
	//-----------------------------
	//生成時に処理する初期化処理を記述
	//-----------------------------
	this->taskName = "Kanetuki";	//検索時に使うための名を登録する
	__super::Init(taskName);		//Taskwaterect内の処理を行う

	Fire_MovetimeReset();
	CreateObject(Cube, pos, Vec2(64, 64), 0);
	this->SetSwitchFlag(target);

	cout << "加熱器　初期化" << endl;
	//サウンドに関する情報
	startflag = false;
	nowplay = false;
	//サウンドの生成
	sound.create(soundname, true);
	//サウンドの生成　　着火
	soundstart.create(startsoundname, false);

	return true;
}
void Kanetuki::Fire_MovetimeReset()
{
	Fire_movetime = 0;
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

	//サウンド関係
	//炎の音声再生
	this->nowplay = sound.isplay();
	if (switchflag)
	{
		if (startflag)
		{
			sound.play();
		}
	}
	//着火の音声再生
	if (switchflag)
	{
		if (startflag)
		{
			soundstart.play();
			startflag = false;
		}
	}
	if (switchflag == false)
	{
		if (nowplay)
		{
			sound.stop();
		}
		startflag = true;
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
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
	{
		//水との当たり判定
		if ((*id)->hit(*this))
		{	//　個体　⇒　液体
			if ((*id)->GetState() == Water::State::SOLID)
			{
				Fire_movetime++;
				//一定の時間が経ったら・・・
				if (Fire_movetime >= Fire_time_SOLID)
				{
					//液体にする
					(*id)->SetState(Water::State::LIQUID);
					Fire_MovetimeReset();
				}
			}
			//液体　⇒　水蒸気
			if ((*id)->GetState() == Water::State::LIQUID)
			{
				Fire_movetime++;
				//一定の時間が経ったら・・・
				if (Fire_movetime >= Fire_time_LIQUID)
				{
					//水蒸気にする
					(*id)->SetState(Water::State::GAS);
					Fire_MovetimeReset();
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
	//サウンドファイル名	
	startsoundname = "fire1.wav";
	soundname = "fire2.wav";
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

Kanetuki::SP Kanetuki::Create(Vec2& pos, std::shared_ptr<Switch>& target, bool flag_)
{
	Kanetuki::SP to = Kanetuki::SP(new Kanetuki());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos, target))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}