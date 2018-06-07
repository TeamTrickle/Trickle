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

	//拡大機能
	float Volume;

private:
	bool Initialize(Vec2&);
	bool Finalize();
	void UpDate();
	void Render2D();
	GoalTimeUI();

	//拡大機能関連
	void MoveVolume();
	void ResetVolume();
public:
	typedef std::shared_ptr<GoalTimeUI> SP;
	static GoalTimeUI::SP Create(Vec2& pos, bool = true);
	virtual ~GoalTimeUI();

};