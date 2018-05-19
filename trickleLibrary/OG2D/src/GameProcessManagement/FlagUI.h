#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

#include "Task\Task_Result.h"
class FlagUI : public GameObject, public TaskObject
{
public:

public:
	void FalgJudge(int);
private:
	Texture image[2];
	int Resultflag;
	int targetflag;
	bool flagactive;
	void SetResultflag();
	const Box2D Src = Box2D(0, 0, 322, 322);
public:
	std::string taskName;
	virtual ~FlagUI();
	typedef std::shared_ptr<FlagUI> SP;
	static FlagUI::SP Create(Vec2& pos,int targetflag,bool = true);
	FlagUI();
	//-------------
	//•ÏX‚µ‚È‚¢‚±‚Æ
	//-------------
	bool Initialize(Vec2& pos,int&);//‰Šú‰»ˆ—
	void UpDate();					//XVˆ—
	void Render2D();				//•`‰æˆ—
	bool Finalize();				//‰ğ•úˆ—
};