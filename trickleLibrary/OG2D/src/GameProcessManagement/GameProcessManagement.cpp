#include "GameProcessManagement.h"
using namespace std;

//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする

bool GameProcessManagement::Initialize()
{
	//-----------------------------
	//生成時に処理する初期化処理を記述
	//-----------------------------
	this->taskName = "GameProcessManagement";		//検索時に使うための名を登録する
	__super::Init(taskName);		//TaskObject内の処理を行う

	gameclear_flag = false;                 //初期値はfalseにしておく
	timer.Start();							//タイマーをスタートさせる

	return true;
}
void GameProcessManagement::UpDate()
{
	//--------------------
	//更新時に行う処理を記述
	//--------------------

	Goal_Check();                        //ゴールをしているのかどうか？
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
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		goals.clear();                           //vectorを解放
		//自分を消す場合はKillを使う
		this->Kill();
	}
	return true;
}
void GameProcessManagement::Set_Goal(GameObject* goal)
{
	if (goal->objectTag != "Goal")           //オブジェクトタグの確認をする
	{
		return;
	}
	goals.push_back(goal);                   //push.backをする
}
void GameProcessManagement::Goal_Check()
{
	for (auto g : goals)
	{
		if (g->objectTag == "Goal")          //オブジェクトタグがGoalならば・・・
		{
			if (((Goal*)g)->cleared)
			{
				if (!gameclear_flag)		//1回だけ発動させることでストップを維持させる
				{
					timer.Pause();			//タイマーをストップする
				}
				gameclear_flag = true;		//フラグをtrueにする
				return;
			}
		}
	}
	timer.Frame_Set();			            //フレーム時間を格納する
	gameclear_flag = false;
}
void GameProcessManagement::Goal_Event()
{
	if (gameclear_flag)						//ゲームフラグがtrueになったら・・・
	{
		timer.Stop();						//タイマーの時間を元に戻す
		File_Writing();						//フレームを書き込み
		//結果画面へ行く

	}
}
void GameProcessManagement::File_Writing()
{
	ofstream fin(TimeFilePath);				//ファイルのパスの指定
	fin << timer.Get_frame();				//タイマーのフレーム数を書き込み
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

}

GameProcessManagement::~GameProcessManagement()
{
	this->Finalize();
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