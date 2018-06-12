#pragma once
//必要読み込みファイル
#include "OGSystem\OGsystem.h"

class Result : public TaskObject
{
	//-------------------------------------------
	//各自で制作するときに使用するものはここに記述する
	//-------------------------------------------
public:
	/*
	アドレスを代入させます
	■引数　Timer アドレス値を受け継ぐ
	■戻り　なし
	*/

	enum Achievement
	{
		Flag1 = 1 << 0,		//フラグ1
		Flag2 = 1 << 1,		//フラグ2
		Flag3 = 1 << 2,		//フラグ3
		Flag4 = 1 << 3,		//フラグ4
		Master = 0x0F,		//全てのフラグ
	};
	enum CreateFlag
	{
		NON = 0,			//全てを生成した
		Timeui =  1 << 0,	//タイムUIの表示
		Starui =  1 << 1,	//☆の表示
		Effect =  1 << 2,	//☆のEffect
		Clearui = 1 << 3,	//クリアUIの表示
	};

	//フラグ関連
	void Flag_Input(Achievement);
	int  Get_Flag();
	void Flag_Judge();
	bool Flag_Judge(Achievement, Achievement);
	bool Flag_Judge(Achievement, Achievement, Achievement);
	void Flag_Judge_Clear();

	//ゴールのタイム関連
	int  GetFrameTime();
	void Result_DataInput();

	//UIの出現について
	void UI_Think();
	void UI_Create();					//フラグによって生成させる


private:
	struct CreateTask
	{
		int createflag;						//生成したフラグ
		int nextflag;						//次に生成するフラグ
		void SetCreateFlag(CreateFlag);
		void SetNextFlag(CreateFlag);
		void ResetCreateFlag();
		void ResetNextFlag();
	};
	CreateTask createtask;
	int Flag;
	int FrameTime;				//結果タイムを格納する

	//結果の際に必要なポインタ　または　ファイルの読み込む


	//ファイルの出力
	const char* TimeFilePath = "./data/Result/Result.dat";

	//画像関連
	Texture image;
	const Box2D backSrc = { 0,0,1280,720 };
	Texture maptile;
	const Box2D maptileSrc = { 0,0,256,256 };
	//------------------
	//固定化されている処理
	//------------------

public:
	std::string taskName;
	virtual ~Result();
	typedef std::shared_ptr<Result> SP;
	static Result::SP Create(bool = true);
	Result();
	//-------------
	//変更しないこと
	//-------------
	bool Initialize();		//初期化処理
	void UpDate();			//更新処理
	void Render2D();		//描画処理
	bool Finalize();		//解放処理
};