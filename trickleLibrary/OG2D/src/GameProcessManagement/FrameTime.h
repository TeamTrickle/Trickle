#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class FrameTimeUI : public GameObject, public TaskObject 
{
	typedef std::shared_ptr<FrameTimeUI> SP;
	//タスク関連
	std::string taskName;

	//画像関連
	Texture image;
	const Box2D Src = { 0,0,64,128 };

	//基本の情報
	int getframetime;
	std::vector<int> frametime;
	int digitnumberLength;
	int digitSelectnumber;
	bool active;
	const int N = 10;		//1の位ごとに数値を取れる設定
	
	

	bool Finalize();
	void UpDate();
	void Render2D();
	void SetFrameTime();
	void SetVector();

	int  SetDigitNumber();		//フレームタイムの桁数を入力する
	void DigitNumberReset();	//フレームタイムの桁数をリセットする
	int  GetDigitNumber();		//フレームタイムの桁数を返す
	void TargetTime();			//ターゲットのタイムを代入する

	//Easing関連
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
};