#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class FrameTimeUI : public GameObject, public TaskObject 
{
	typedef std::shared_ptr<FrameTimeUI> SP;
	//タスク関連
	std::string taskName;
	bool Finalize();
	void UpDate();
	void Render2D();


	//画像関連
	Texture image;
	const Box2D Src = { 0,0,64,128 };
	int digitSelectnumber;				//この数字によって描画に変化が起きる
	int randomSelectnumber;				//ドラムロール中はこちらで描画する
	//画像関連　大きさ
	int  ScaleanimetionCnt;				//一瞬だけ大きさを変えるアニメーションカウント
	bool Scaleanimeflag;				//大きさ変化させたフラグ

	//基本の情報
	struct Time
	{
		int outputtime[4];				//ゴールタイムの格納
		int Inputtime;					//配列へ入れるためのタイム

		void InitTime();							//時間を設定
		void SetTime();								//配列に代入する
		int GetMinutes();							//分を返す
		int GetSecond();							//秒を返す

	private:
		int minutes;					//分
		int second;						//秒
		size_t digit;					//数字の桁数
		std::string tostringtime;		//数字の桁数を計算するのに必要

		std::string Set_toString(int&);				//引数の数字をStringとして代入する
		void SetDigitLength(std::string&);			//数字の桁数を出力する
		int toInt(std::string&, int loop);			//string型　⇒　Int型にして一文字だけ取り出して配列に送る　
		int toSecond();								//秒の計算
		int toMinutes();							//分の計算
	};
	
	//ドラムロール関連
	int Random();					//ランダムの値を返す
	void ResetMoveCnt();			//アニメーションカウントをリセットする
	void ResetMoveCnt(int& moveCnt);//ターゲットのカウントをリセットする
	void ResetDramRollisPlay();		//フラグのリセットをする
	void DramRoll(int time);		//ドラムロール
	bool MoveCntJudge(int& moveCnt,int time);	//一定の時間が経ったらtrueで終了
	int  moveCnt;					//ドラムロールアニメーションカウント
	bool dramrollisPlay;			//今ドラムロール中かどうか？


	//Easing関連
	FrameTimeUI::Time goaltime;	//ゴールタイム
	Easing easingX;				//X座標のEasing
	Vec2 PrePos;				//保存しておく座標値
	bool easingEnd;				//Easingが終了したかを返す
	

public:
	static FrameTimeUI::SP Create(Vec2& pos,int digitSelect,int& resulttime,bool = true);
	bool Initialize(Vec2& pos,int digitSelect,int& resulttime);
	FrameTimeUI();
	virtual ~FrameTimeUI();

	//Easing関連
	bool GetEasingEnd();

	//ドラムロール関連
	bool GetDramRollIsPlay();
};