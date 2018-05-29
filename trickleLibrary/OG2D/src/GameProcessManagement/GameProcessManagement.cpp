#include "GameProcessManagement.h"
using namespace std;
//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする
#include "Goal\Goal.h"
#include "Task\Task_Result.h"
#include "GameProcessManagement\GameClearCamera.h"
bool GameProcessManagement::Initialize()
{
	//-----------------------------
	//生成時に処理する初期化処理を記述
	//-----------------------------
	this->taskName = "GameProcessManagement";		//検索時に使うための名を登録する
	__super::Init(taskName);		//TaskObject内の処理を行う

	auto gameClearcamera = GameClearCamera::Create();

	gameclear_flag = false;                 //初期値はfalseにしておく
	pause_flag = false;
	timer = Timer::Create();
	timer->Start();							//タイマーをスタートさせる

	cout << "進行管理クラス　初期化" << endl;
	return true;
}
void GameProcessManagement::UpDate()
{
	//--------------------
	//更新時に行う処理を記述
	//--------------------
	Goal_Check();                        //ゴールをしているのかどうか？
	Goal_Event();
}

void GameProcessManagement::Render2D()
{
	//--------------------
	//描画時に行う処理を記述
	//--------------------
	
}

bool GameProcessManagement::Finalize()
{
	//-----------------------------------------
	//このオブジェクトが消滅するときに行う処理を記述
	//-----------------------------------------
	//次のタスクを作るかかつアプリケーションが終了予定かどうか
	if (timer != nullptr)
	{
		timer->Kill();
	}
	auto goal = OGge->GetTask<Goal>("Goal");
	if (goal != nullptr)
	{
		goal->Kill();
	}
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		//ゴールをしている
		if (gameclear_flag)
		{//ポーズ処理を行っていない
			if (!pause_flag)
			{
				//順番が違うとリザルト画面の表示ができません
				auto result = Result::Create();
				pause_flag = true;
			}
		}
	}
	return true;
}
void GameProcessManagement::Goal_Check()
{
	auto goal = OGge->GetTask<Goal>("Goal");
	if (goal != nullptr)
	{//ゴールがクリアになった
		if (goal->cleared)
		{
			if (!gameclear_flag)
			{
				timer->Pause();
			}
			gameclear_flag = true;
			//クリアしたらこの関数はここで終了するようにする
			return;
		}
		//タイマーを動かす処理
		timer->Frame_Set();
		gameclear_flag = false;
	}	
}
void GameProcessManagement::Goal_Event()
{
	//ゴールをしたら・・・
	if (gameclear_flag)						//ゲームフラグがtrueになったら・・・
	{
		timer->Stop();						//タイマーの時間を元に戻す
		File_Writing();						//フレームを書き込み
	}
}
void GameProcessManagement::File_Writing()
{
	ofstream fin(TimeFilePath);				//ファイルのパスの指定
	fin << timer->Get_frame();				//タイマーのフレーム数を書き込み
	fin << ',';								//,の書き込み
	if (gameclear_flag)
	{
		fin << "GameClear";					//ゲームクリアフラグ
		fin << ',';							//,の書き込み
	}
	else
	{
		fin << "NoGame";					//ゲーム未クリア
		fin << ',';							//,の書き込み
	}
	fin.close();							//ファイルを閉じる
}
//----------------------------
//ここから下はclass名のみ変更する
//ほかは変更しないこと
//----------------------------
GameProcessManagement::GameProcessManagement()
{
	cout << "進行管理クラス　生成" << endl;
}

GameProcessManagement::~GameProcessManagement()
{
	this->Finalize();
	cout << "進行管理クラス　解放" << endl;
}

GameProcessManagement::SP GameProcessManagement::Create(bool flag_)
{
	GameProcessManagement::SP to = GameProcessManagement::SP(new GameProcessManagement());
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