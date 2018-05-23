#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class GoalTimeUI : public GameObject, public TaskObject
{
private:
	std::string taskName;
	Texture image;
	const Box2D Src = {0,0,227,90};
private:
	bool Initialize(Vec2&);
	bool Finalize();
	void UpDate();
	void Render2D();
	GoalTimeUI();
public:
	typedef std::shared_ptr<GoalTimeUI> SP;
	static GoalTimeUI::SP Create(Vec2& pos, bool = true);
	virtual ~GoalTimeUI();
};