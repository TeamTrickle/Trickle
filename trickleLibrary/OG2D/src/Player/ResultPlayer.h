#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
class ResultPlayer : public GameObject , public TaskObject 
{
	Texture image;
	std::string filePath;
	Vec2 moveVec;
	void Move();
	const Box2D Src = { Vec2(0, 0), Vec2(532,519) };
public:
	typedef std::shared_ptr<ResultPlayer> SP;
	ResultPlayer();
	virtual ~ResultPlayer();
	std::string taskName;

	bool Initialize(Vec2& pos,Vec2& speed);
	void UpDate();
	void Render2D();
	bool Finalize();
	static ResultPlayer::SP Create(Vec2 pos,Vec2 speed = Vec2(1,0) ,bool = true);
};