#include "Kanetuki.h"
using namespace std;
Kanetuki::Kanetuki()
{
	
}
Kanetuki::~Kanetuki()
{

}
void Kanetuki::Create(Vec2 pos, Vec2 scale)
{
	Fire_movetime = 0;
	hitBace.CreateObject(Cube, pos, scale, 0);	
}
void Kanetuki::Motion()
{
	hitBace.CollisionProcess = [&](const Object& o_)
	{
		if (o_.objectTag == "Water")
		{
			switch (((Water&)o_).GetState())
			{
			case Water::State::GAS://ƒKƒX‚Ìê‡
				break;
			case Water::State::LIQUID://‰t‘Ì‚Ìê‡
				Fire_movetime++;
				if (Fire_movetime >= Fire_time_LIQUID)
				{
					((Water&)o_).SetState(Water::State::GAS);
					Fire_movetime = 0;
				}
				break;
			case Water::State::SOLID://ŒÂ‘Ì‚Ìê‡
				Fire_movetime++;
				if (Fire_movetime >= Fire_time_SOLID)
				{
					((Water&)o_).SetState(Water::State::SOLID);
					Fire_movetime = 0;
				}
				break;
			default:
				break;
			}
		}
	};
}
void Kanetuki::CheckHit()
{
	hitBace.CollisionProcess = [&](const Object& o_)
	{
		if (((Water&)o_).objectTag == "Water")
		{
			Motion();
		}
	};
}