#pragma once
//必要読み込みファイル
#include "OGSystem\OGsystem.h"
#include "GameProcessManagement/Timer.h"
#include "../OGSystem/Easing/easing.hpp"

class Result :public TaskObject {
public:
	std::string taskName;
	typedef std::shared_ptr<Result> SP;
	static Result::SP Create(bool flag = true);
	Result();
	~Result();

	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();

	//サウンドの生成
	Sound sound;
	Sound soundstar;
	Sound sounddrum;

	//エフェクトのカウント
	int effCounter;

private:
	enum Mode {
		Non,
		Mode1,		//プレイヤ、ResultUI出現から停止まで
		Mode2,		//TIME、星の枠出現から停止まで
		Mode3,		//ドラムロールからクリアタイムの表示まで
		Mode4,		//星出現からはまるまで
		Mode5,		//プレイヤ喜び、CLEARUI出現から停止まで
		Mode6,		//プレイヤ退場、終了
		Mode7,		//退場後でも星と時間表示をとどまらせておく
	};
	Mode nowMode;

	Texture backTex;
	//Texture resultTex;
	Texture frameTex;
	//Texture timeTex;
	//Texture starFrameTex;
	Texture starTex;
	Texture clearTex;
	Texture fontui;			//仮、本番で消す
	Texture numberui;
	Texture stareffectTex;
	//花びらのエフェクト
	Texture petalTex1;
	Texture petalTex2;
	Texture petalTex3;
	Texture petalTex4;
	Texture petalTex5;

	//サウンドのファイル名格納
	std::string soundname;
	std::string starsoundname;
	std::string drumsoundname;

	struct resultUI {
		Vec2 pos;
		Vec2 nowWH;
		Vec2 preWH;
		Easing easeX;
		Easing easeY;
		Easing easeW;
		Easing easeH;
		float bezcnt;
		int angle;
	};
	resultUI frame;
	resultUI result;
	resultUI time;
	resultUI number[4];
	resultUI starFrame[3];
	resultUI star[3];
	resultUI clear;


	int cnt;
	int num[4];
	bool starFlag[3];
	bool starturn[3];
	bool effectStarFlag[3];			//☆エフェクトを出力したかどうかのフラグ
	float starAngle;

	unsigned timer[4];
	int test1, test2;
	__int8 maxTrueNumber;
	void RoadData();
};

//class Result : public TaskObject
//{
//	//-------------------------------------------
//	//各自で制作するときに使用するものはここに記述する
//	//-------------------------------------------
//public:
//	/*
//	アドレスを代入させます
//	■引数　Timer アドレス値を受け継ぐ
//	■戻り　なし
//	*/
//	enum CreateFlag
//	{
//		NON = 0,			//全てを生成した
//		Timeui =  1 << 0,	//タイムUIの表示
//		Starui =  1 << 1,	//☆の表示
//		Effect =  1 << 2,	//☆のEffect
//		Clearui = 1 << 3,	//クリアUIの表示
//	};
//private:
//	//ゴール関連
//	void Result_DataInput();
//
//	//UIの出現について
//	void UI_Think();
//	void UI_Create();					//フラグによって生成させる
//
//	//その他の関数
//	int  to_String(std::string&);
//
//private:
//	struct CreateTask
//	{
//		int createflag;						//生成したフラグ
//		int nextflag;						//次に生成するフラグ
//		void SetCreateFlag(CreateFlag);
//		void SetNextFlag(CreateFlag);
//		void ResetCreateFlag();
//		void ResetNextFlag();
//	};
//	CreateTask createtask;
//
//
//	int Flag;
//	int FrameTime;				//結果タイムを格納する
//
//	//結果の際に必要なポインタ　または　ファイルの読み込む
//
//
//	//ファイルの出力
//	const char* TimeFilePath = "./data/Result/Result.dat";
//
//	//画像関連
//	Texture image;
//	const Box2D backSrc = { 0,0,1280,720 };
//	Texture maptile;
//	const Box2D maptileSrc = { 0,0,256,256 };
//	//------------------
//	//固定化されている処理
//	//------------------
//
//public:
//	std::string taskName;
//	virtual ~Result();
//	typedef std::shared_ptr<Result> SP;
//	static Result::SP Create(bool = true);
//	Result();
//	//-------------
//	//変更しないこと
//	//-------------
//	bool Initialize();		//初期化処理
//	void UpDate();			//更新処理
//	void Render2D();		//描画処理
//	bool Finalize();		//解放処理
//
//	//他のクラスで使用する
//	int GetFlag();
//};