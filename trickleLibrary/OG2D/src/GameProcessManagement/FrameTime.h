#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class FrameTimeUI : public GameObject, public TaskObject 
{
	typedef std::shared_ptr<FrameTimeUI> SP;
	std::string taskName;
	Texture image;
	int getframetime;
	std::vector<int> frametime;
	int digitnumberLength;
	int digitSelectnumber;

	const Box2D Src = { 0,0,64,128 };
	const int N = 10;		//1の位ごとに数値を取れる設定

	bool Finalize();
	void UpDate();
	void Render2D();
	void SetFrameTime();
	void SetVector();
	int  SetDigitNumber();		//フレームタイムの桁数を入力する
	void DigitNumberReset();	//フレームタイムの桁数をリセットする
	int  GetDigitNumber();		//フレームタイムの桁数を返す
	int  GetResultFrameTime();	//リザルト画面からのタイムを返す
	int  TargetTime();			//ターゲットのタイムを代入する
public:
	static FrameTimeUI::SP Create(Vec2& pos,int digitSelect,bool = true);
	bool Initialize(Vec2& pos,int digitSelect);
	FrameTimeUI();
	virtual ~FrameTimeUI();
};