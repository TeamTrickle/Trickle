#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class CameraManager
{
	Box2D Range;
	Box2D Size;
	Box2D RealRange;
	Vec2 est;
	Box2D pretarget;
	GameObject* target;
public:
	CameraManager();
	~CameraManager();
	void SetObject(GameObject*);
	void SetRange(Box2D&);
	void SetSize(Box2D&);
	void move();
	void DeleteObject();
};

//カメラの即移動防止のための拡張機能
class CameraEasing
{
	Easing easing_x;
	Easing easing_y;
	Vec2* start;
	Vec2* end;
public:
	CameraEasing();
	~CameraEasing();
	void Set(const Vec2& end);
	void CameraMove();
	bool IsPlay();
public:
};