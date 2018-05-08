#pragma once
#include "Object\Object.h"
#include "Water\water.h"

class Water;

class Kanetuki : public Object
{
public:
	Kanetuki();
	~Kanetuki();
	void Create(Vec2, Vec2);	//À•W’l@“–‚½‚è”»’èƒTƒCƒY
	void SetWaterPool(std::vector<Water*> *);
	void Update();
	Object hitBace;
private:
	const int Fire_time_LIQUID = 70;	//‰Á”M‚·‚éŠÔ ‰t‘Ì
	const int Fire_time_SOLID = 40;	    //‰Á”M‚·‚éŠÔ ŒÂ‘Ì
	int Fire_movetime;					//”R‚â‚·ŠÔ‚ğŠi”[‚·‚é
	
	//typedef std::vecor<Water*> WaterPool;
	std::vector<Water*> *water;		

	//ó‘Ô‘JˆÚ
	void toSteam(Water*);		//…‚©‚ç…ö‹C‚É‚·‚é
};