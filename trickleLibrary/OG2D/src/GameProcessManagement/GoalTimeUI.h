#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class GoalTimeUI : public GameObject, public TaskObject
{
private:
	//タスク関連
	std::string taskName;

	//画像関連
	Texture image;
	const Box2D Src = {0,0,227,90};

	//Easing用変数
	Easing easingX;
	Vec2 PrePos;		//Easing用に保存しておく座標値
	bool easingEnd;

	//拡大機能
	float Volume;

private:
	bool Initialize(Vec2&);
	bool Finalize();
	void UpDate();
	void Render2D();
	GoalTimeUI();

	void MoveVolume();
	void ResetVolume();
public:
	typedef std::shared_ptr<GoalTimeUI> SP;
	static GoalTimeUI::SP Create(Vec2& pos, bool = true);
	virtual ~GoalTimeUI();

	//リザルトで使用する関数
	bool GetEasingEnd();
};