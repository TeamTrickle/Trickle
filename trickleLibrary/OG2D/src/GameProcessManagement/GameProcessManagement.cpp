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
	timer.Initialize();                      //タイマーのタイムをゼロクリアする
}
void GameProcessManagement::Update()
{
	timer.Update();                          //タイマー時間の出力・計算をしている
	Goal_Check();
	Goal_Event();                            //ゲームクリアイベントを呼び出す
}
void GameProcessManagement::Set_Goal(Object* goal)
{
	//if (goal->objectTag != "Goal")           //オブジェクトタグの確認をする
	//{
	//   return;
	//}
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
				gameclear_flag = true;
				return;
			}
		}
	}
	gameclear_flag = false;
}
void GameProcessManagement::Goal_Event()
{
	if (gameclear_flag)
	{
		cout << "ゲームクリア" << endl;
	}
}