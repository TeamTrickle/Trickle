#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class MissionUI : public GameObject, public TaskObject
{
private:
	std::string taskName;
	Texture image;

	Easing easingY;
	const Box2D Src = {0,0,616,101};
private:
	bool Initialize();
	bool Finalize();
	void UpDate();
	void Render2D();

	MissionUI();

	void EasingMove();
public:
	typedef std::shared_ptr<MissionUI> SP;
	static MissionUI::SP Create(bool = true);
	virtual ~MissionUI();

};