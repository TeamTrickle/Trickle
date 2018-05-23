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