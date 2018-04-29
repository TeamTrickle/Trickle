#include "GameProcessManagement.h"
using namespace std;
GameProcessManagement::GameProcessManagement()
{
	cout << "進行管理クラス初期化" << endl;
}
GameProcessManagement::~GameProcessManagement()
{
	cout << "進行管理クラス解放" << endl;
	goals.clear();                           //vectorを解放
}
void GameProcessManagement::Initialize()
{
	gameclear_flag = false;                  //初期値はfalseにしておく
	timer.Start();							//タイマーをスタートさせる
}
void GameProcessManagement::Update()
{
	Goal_Check();                        //ゴールをしているのかどうか？
}
void GameProcessManagement::Set_Goal(Object* goal)
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
TaskFlag GameProcessManagement::Goal_Event()
{
	TaskFlag nowtask = Task_Game;
	if (gameclear_flag)						//ゲームフラグがtrueになったら・・・
	{
		timer.Stop();						//タイマーの時間を元に戻す
		File_Writing();						//フレームを書き込み
		nowtask = Task_Ruselt;				//結果画面へ移る
	}
	return nowtask;
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
