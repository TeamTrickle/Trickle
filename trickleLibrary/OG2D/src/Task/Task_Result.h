#pragma once
#include "Object\Object.h"
#include "Win\WinMain.h"
#include "GameProcessManagement\Timer.h"


class Result
{
public:
	/*
	コンストラクタ
	■引数　なし
	■戻り　なし
	*/
	Result();

	/*
	デストラクタ
	■引数　なし
	■戻り　なし
	*/
	~Result();

	/*
	特になし
	■引数　なし
	■戻り　なし
	*/
	void Initialize();

	/*
	タスクを遷移する判定をとる
	■引数　なし
	■戻り　なし
	*/
	TaskFlag Update();

	/*
	リザルト画面を描画をします
	■引数　なし
	■戻り　ゲームのタスク
	*/
	void Render();

	/*
	使用した画像を解放します
	■引数　なし
	■戻り　なし
	*/
	void Finalize();

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

	//結果の際に必要なポインタ　または　ファイルの読み込む
	const char* TimeFilePath = "./data/Result/Result.dat";
};