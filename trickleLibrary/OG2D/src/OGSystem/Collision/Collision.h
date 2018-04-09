#pragma once
#include "OGSystem\_OGsystem.h"
#include "OGSystem\GameEngine\GameEngine.h"
class CollisionBox;
class CollisionCircle;
class CollisionBox
{
public:
	Box2D hitBase;
	bool hitBox(CollisionBox b);
	bool hitCircle(CollisionCircle b);
	void Rotate(float _angle);
	float angle;
private:
	void hitdraw();
};
class CollisionCircle
{
public:
	Circle hitBase;
	bool hitBox(CollisionBox b);
	bool hitCircle(CollisionCircle b);
private:
};