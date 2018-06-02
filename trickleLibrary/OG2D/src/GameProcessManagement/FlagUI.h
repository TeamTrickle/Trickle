#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

#include "Task\Task_Result.h"
class FlagUI : public GameObject, public TaskObject
{
public:
	void FalgJudge(int);
private:
	int Resultflag;
	int targetflag;
	bool flagactive;
	void SetResultflag();

	//Easing関連
	Vec2 PrePos;
	Easing easingX;
	void EasingMove();

	//画像関連
	Texture image[2];
	const Box2D Src = Box2D(0, 0, 322, 322);
public:
	std::string taskName;
	virtual ~FlagUI();
	typedef std::shared_ptr<FlagUI> SP;
	static FlagUI::SP Create(Vec2& pos,int targetflag,bool = true);
	FlagUI();
	//-------------
	//変更しないこと
	//-------------
	bool Initialize(Vec2& pos,int&);//初期化処理
	void UpDate();					//更新処理
	void Render2D();				//描画処理
	bool Finalize();				//解放処理

	//リザルトタスクで使用する関数
	bool EasingEnd();				//easingの演出が終了しているか？を判定します
};