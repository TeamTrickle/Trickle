#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class MissionUI : public GameObject, public TaskObject
{
private:
	std::string taskName;
	Texture image;
	const Box2D Src = {0,0,616,101};
private:
	bool Initialize(Vec2&);
	bool Finalize();
	void UpDate();
	void Render2D();
	MissionUI();
public:
	typedef std::shared_ptr<MissionUI> SP;
	static MissionUI::SP Create(Vec2& pos, bool = true);
	virtual ~MissionUI();
};