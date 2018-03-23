#pragma once
//______________________________//
//|ゲームオブジェクト            |//
//|履歴：2018/03/20金子翔       |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
enum Objform
{
	Non,
	Ball,
	Cube,
};
class Object
{
public:
	Objform objform;
	Vec2 position;
	Vec2 Scale;
	float angle;
	CollisionBox collisionCube;
	CollisionCircle collisionBall;
	bool Gravity;
	bool hit(Object o);
	Object();
	Object(Objform form, Vec2 _posi, Vec2 _Sca, float _ang);
	~Object();
	void CreateObject(Objform form, Vec2 _posi, Vec2 _Sca, float _ang);
private:
};