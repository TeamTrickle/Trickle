#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class CameraManager
{
	Box2D Range;
	Box2D Size;
	GameObject* target;
	CameraManager();
	~CameraManager();
	void SetObject(GameObject*);
	void SetRange(Box2D&);
	void SetSize(Box2D&);
	void move();
};