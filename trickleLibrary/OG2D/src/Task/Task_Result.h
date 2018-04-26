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

	void Timer_Input();
private:
	Texture image;
	

	const std::string _FilePath = "";

	int Flag;

	enum Achievement
	{
		Goal  = 1,		//ゴールしている
		Color = 2,		//カラー
	};

	//結果の際に必要なポインタ　または　ファイルの読み込む
	FILE* file;			//ファイルを読み込み用
	const char* TimeFilePath = "./data/Result.dat";
};