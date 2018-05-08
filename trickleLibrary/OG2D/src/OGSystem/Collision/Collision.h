#pragma once
#include "OGSystem\_OGsystem.h"
#include "OGSystem\GameEngine\GameEngine.h"
class CollisionBox;
class CollisionCircle;
class CollisionBox
{
public:
	Box2D hitBase;						//“–‚½‚è”»’è	
	bool hitBox(CollisionBox& b);		//‹éŒ`‚Æ‚Ì”»’è
	bool hitCircle(CollisionCircle& b);	//‰~‚Æ‚Ì”»’è
	void Rotate(float _angle);			//‰ñ“]‚ð“K—p
	float angle;						//‰ñ“]’l
private:
	void hitdraw();						//Šm”F—p
};
class CollisionCircle
{
public:
	Circle hitBase;						//“–‚½‚è”»’è
	bool hitBox(CollisionBox& b);		//‹éŒ`‚Æ‚Ì”»’è
	bool hitCircle(CollisionCircle& b);	//‰~‚Æ‚Ì”»’è
private:
};