#pragma once
//__________________________
//|                      //|
//|履歴　2018/04/14 横尾 //|
//|履歴　2018/04/19 横尾 //|
//|履歴　2018/04/26 横尾 //|
//|______________________//|
#include "Object\Object.h"
//関連するプロジェクト//
#include "Goal\Goal.h"
#include "Timer.h"
#include "Win\WinMain.h" //タスクの遷移に必要
#include "Task\Task_Result.h"

class Goal;

class GameProcessManagement : public  Object
{
public:
	/*
	コンストラクタを呼び出す
	■引数　なし
	■戻り　なし
	*/
	explicit GameProcessManagement();


	/*
	デストラクタを呼び出す
	■引数　なし
	■戻り　なし
	*/
	virtual ~GameProcessManagement();


	/*
	フラグの初期化・ゲーム用のタイムを初期化する
	■引数  なし
	■戻り　なし
	*/
	void Initialize();


	/*
	1フレームごとに関数を呼び出す関数
	■引数　なし
	■戻り　なし
	*/
	void Update();    


	/*
	ゴールオブジェクトの追加をします
	■引数　Object*　追加したいゴールオブジェクト
	■戻り　なし
	*/
	void Set_Goal(Object*);


	/*
	ゴールの判定を行います
	■引数　なし
	■戻り　なし
	*/
	void Goal_Check();


	/*
	ゲームのフラグによって変化するイベント管理関数
	■引数　なし
	■戻り　ゲームフラグを返す
	*/
	TaskFlag Goal_Event();


	void File_Writing();				//フレームを書きこむ
private:

	bool gameclear_flag;               //様々なフラグを格納する
	std::vector<Object*>goals;         //ゴール判定を取るVector
	Timer timer;                       //タイマーのセットをする

	FILE* Timefile;					  //タイムを出力するタイム
	const char* TimeFilePath = "./data/Result.dat";
};