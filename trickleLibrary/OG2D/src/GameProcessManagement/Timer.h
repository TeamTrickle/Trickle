#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

//__________________________
//|                      //|
//|履歴　2018/04/14 横尾 //|
//|履歴　2018/04/15 横尾 //|
//|履歴　2018/04/19 横尾 //|
//|履歴　2018/04/26 横尾 //|
//|______________________//|
class Timer : public GameObject, public TaskObject,public Time
{
	//-------------------------------------------
	//各自で制作するときに使用するものはここに記述する
	//-------------------------------------------
public:
	/*
	タイマーの時間をフレーム時間に格納する
	■引数　なし
	■戻り　なし
	*/
	void Frame_Set();

	int Get_frame();
private:
	int frame_time;                                //Timeクラスから時間を受け取る関数
	//------------------
	//固定化されている処理
	//------------------
public:
	std::string taskName;
	virtual ~Timer();
	typedef std::shared_ptr<Timer> SP;
	static Timer::SP Create(bool = true);
	Timer();
	//-------------
	//変更しないこと
	//-------------
	bool Initialize();		//初期化処理
	void UpDate();			//更新処理
	void Render2D();		//描画処理
	bool Finalize();		//解放処理
};