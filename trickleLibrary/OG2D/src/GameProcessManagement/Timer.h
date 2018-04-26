#pragma once
#include "Object\Object.h"
#include "OGSystem\Timer\glTimer.h"
#include <iostream>

//__________________________
//|                      //|
//|履歴　2018/04/14 横尾 //|
//|履歴　2018/04/15 横尾 //|
//|履歴　2018/04/19 横尾 //|
//|履歴　2018/04/26 横尾 //|
//|______________________//|

class Timer : public Time
{
public:
	/*
	コンストラクタ
	■引数　なし
	■戻り　なし
	*/
	Timer();


	/*
	デストラクタ
	■引数　なし
	■戻り　なし
	*/
	~Timer();


	/*
	タイマーのゼロクリアをする
	■引数　なし
	■戻り　なし
	*/
	void Initialize();


	/*
	タイマーの関数をまとめて呼び出す
	■引数　なし
	■戻り　なし
	*/
	void Update();


	/*
	タイマーの時間を1フレームづつ計測する
	■引数　なし
	■戻り　なし
	*/
	void Instrumentation();

	/*
	指定したタイマーの時間をコマンドプロンプトに出力する
	■引数　Timer& 出力したいタイマー
	■戻り　なし
	*/
	void Instrumentation_output(Timer&);

	/*
	タイマーの時間をフレーム時間に格納する
	■引数　なし
	■戻り　なし
	*/
	void Frame_Set();

	int Get_frame();
private:
	int frame_time;                                //Timeクラスから時間を受け取る関数
};