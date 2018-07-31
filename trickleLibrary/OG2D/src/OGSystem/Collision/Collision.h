///Box2D,Circleを使用し当たり判定を行うclass
#pragma once
#include "OGSystem\_OGsystem.h"

class CollisionBox;
class CollisionCircle;
class CollisionBox
{
public:
	Box2D hitBase;						//当たり判定	
	bool hitBox(const CollisionBox& b);		//矩形との判定
	bool hitCircle(const CollisionCircle& b);	//円との判定
	void Rotate(const float _angle);	//回転を適用
	float angle;						//回転値
private:
	void hitdraw();						//確認用
};
class CollisionCircle
{
public:
	Circle hitBase;						//当たり判定
	bool hitBox(const CollisionBox& b);		//矩形との判定
	bool hitCircle(const CollisionCircle& b);	//円との判定
private:
};