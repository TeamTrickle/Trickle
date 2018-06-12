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
public:
	enum Achievement
	{
		Flag1 = 1 << 0,		//フラグ1
		Flag2 = 1 << 1,		//フラグ2
		Flag3 = 1 << 2,		//フラグ3
		Flag4 = 1 << 3,		//フラグ4
		Master = 0x0F,		//全てのフラグが達成した
	};
private:
	//ミッション項目関連
	struct Mission
	{
		//フラグ関連
		void Flag_Input(Achievement);
		void Flag_Judge(unsigned short& mapnumber , std::ofstream& fin);
		void Flag_Judge_Clear();

		//フラグを格納する変数
		int  Flag;
	};


	//各自変数

	//ミッション関連
	Mission mission;					//達成項目の条件を扱う

	//基本の情報
	bool gameclear_flag;                 //様々なフラグを格納する
	bool pause_flag;					 //ポーズ画面からタイトルへ戻れされる場合の対策

	//タイマー関連
	Timer::SP timer;                     //タイマーのセットをする

	

	const char* TimeFilePath = "./data/Result/Result.dat";

private:
	//ゴール判定関連
	void Goal_Check();		//ゴールの判定をチェックします
	void Goal_Event();		//全てがゴール状態ならリザルト画面に行きます

	//リザルト画面にデータを送る関数関連
	void File_Writing();				 //フレームを書きこむ
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

	//他のクラスで使用する関数
	bool isAllGoal();		//全てがゴールをしているかどうかを返します
	int  GetFlag();			//現在のステージミッションフラグを返します
};