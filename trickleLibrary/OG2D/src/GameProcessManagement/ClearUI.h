#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class ClearUI : public GameObject, public TaskObject
{
private:
	std::string taskName;
	Texture image;
	const Box2D Src = {0,0,269,85};
private:
	bool Initialize(Vec2&);
	bool Finalize();
	void UpDate();
	void Render2D();
	ClearUI();
public:
	virtual ~ClearUI();
	typedef std::shared_ptr<ClearUI> SP;
	static ClearUI::SP Create(Vec2& pos, bool = true);
};