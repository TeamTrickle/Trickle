//__________________________
//|                      //|
//|履歴　2018/04/14 横尾 //|
//|履歴　2018/04/19 横尾 //|
//|履歴　2018/04/26 横尾 //|
//|______________________//|
#pragma once
//必要読み込みファイル
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Timer.h"

class GameProcessManagement : public GameObject,public TaskObject
{
	//-------------------------------------------
	//各自で制作するときに使用するものはここに記述する
	//-------------------------------------------
public:
	/*
	ゴールオブジェクトの追加をします
	■引数　Object*　追加したいゴールオブジェクト
	■戻り　なし
	*/
	//void Set_Goal();


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
	void Goal_Event();

	void File_Writing();				 //フレームを書きこむ
private:
	bool gameclear_flag;                 //様々なフラグを格納する
	bool pause_flag;					 //ポーズ画面からタイトルへ戻れされる場合の対策
	Timer::SP timer;                     //タイマーのセットをする

	const char* TimeFilePath = "./data/Result/Result.dat";

	//------------------
	//固定化されている処理
	//------------------
public:
	std::string taskName;
	virtual ~GameProcessManagement();
	typedef std::shared_ptr<GameProcessManagement> SP;
	static GameProcessManagement::SP Create(bool = true);
	GameProcessManagement();
	//-------------
	//変更しないこと
	//-------------
	bool Initialize();		//初期化処理
	void UpDate();			//更新処理
	void Render2D();		//描画処理
	bool Finalize();		//解放処理
};