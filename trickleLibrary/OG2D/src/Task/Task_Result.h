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

	void Result_DataInput();

	enum Achievement
	{
		Flag1 = 1 << 0,		//フラグ1
		Flag2 = 1 << 1,		//フラグ2
		Flag3 = 1 << 2,		//フラグ3
		Flag4 = 1 << 3,		//フラグ4
	};
	void Flag_Input(Achievement);
	int Get_Flag();
	//フラグのチェック
	bool Flag_Judge();
	bool Flag_Judge(Achievement, Achievement);
	bool Flag_Judge(Achievement, Achievement, Achievement);

	void Flag_Judge_Clear();
private:
	Texture image;


	const std::string _FilePath = "";

	int Flag;
	int FrameTime;				//結果タイムを格納する
								//結果の際に必要なポインタ　または　ファイルの読み込む
	const char* TimeFilePath = "./data/Result/Result.dat";
	//------------------
	//固定化されている処理
	//------------------
public:
	std::string taskName;
	virtual ~Result();
	typedef std::shared_ptr<Result> SP;
	static Result::SP Create(bool);
	Result();
	//-------------
	//変更しないこと
	//-------------
	bool Initialize();		//初期化処理
	void UpDate();			//更新処理
	void Render2D();		//描画処理
	bool Finalize();		//解放処理
};