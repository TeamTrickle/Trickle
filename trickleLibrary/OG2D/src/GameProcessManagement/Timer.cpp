#include "Timer.h"
using namespace std;

//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする

bool Timer::Initialize()
{
	//-----------------------------
	//生成時に処理する初期化処理を記述
	//-----------------------------
	this->taskName = "Timer";		//検索時に使うための名を登録する
	__super::Init(taskName);		//TaskObject内の処理を行う

	//時間のゼロクリア
	frame_time = 0;               //GetTimeの時間を代入する変数
	return true;
}
void Timer::UpDate()
{
	//--------------------
	//更新時に行う処理を記述
	//--------------------
}

void Timer::Render2D()
{
	//--------------------
	//描画時に行う処理を記述
	//--------------------
	Box2D draw(this->position, this->Scale);
	draw.OffsetSize();
}

bool Timer::Finalize()
{
	//-----------------------------------------
	//このオブジェクトが消滅するときに行う処理を記述
	//-----------------------------------------
	//次のタスクを作るかかつアプリケーションが終了予定かどうか
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		//自分を消す場合はKillを使う
		this->Kill();
	}
	return true;
}
void Timer::Frame_Set()
{
	frame_time = GetTime();
}
int Timer::Get_frame()
{
	return frame_time;
}
//----------------------------
//ここから下はclass名のみ変更する
//ほかは変更しないこと
//----------------------------
Timer::Timer()
{

}

Timer::~Timer()
{
	this->Finalize();
}

Timer::SP Timer::Create(bool flag_)
{
	Timer::SP to = Timer::SP(new Timer());
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