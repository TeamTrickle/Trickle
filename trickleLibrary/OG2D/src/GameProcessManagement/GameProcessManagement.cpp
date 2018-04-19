#include "GameProcessManagement.h"
using namespace std;
GameProcessManagement::GameProcessManagement()
{

}
GameProcessManagement::~GameProcessManagement()
{
	goals.clear();                           //vectorを解放
}
void GameProcessManagement::Initialize()
{
	gameclear_flag = false;                  //初期値はfalseにしておく
	
}
void GameProcessManagement::Update()
{
	timer.Update();                      //タイマー時間の出力・計算をしている
	Goal_Check();                        //ゴールをしているのかどうか？
	Goal_Event();                        //ゲームクリアイベントを呼び出す
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
void GameProcessManagement::Goal_Event()
{
	if (gameclear_flag)						//ゲームフラグがtrueになったら・・・
	{
		cout << "ゲームクリア" << endl;		
		timer.Instrumentation_output();		//時間を出力
		timer.Stop();						//タイマーの時間を元に戻す
	}
}