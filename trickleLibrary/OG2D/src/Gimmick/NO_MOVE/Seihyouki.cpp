#include "Seihyouki.h"
using namespace std;
Seihyouki::Seihyouki()
{

}
Seihyouki::~Seihyouki()
{

}
void Seihyouki::Create(Vec2 pos, Vec2 scale)
{
	movetime = 0;
	hitBace.CreateObject(Cube, pos, scale, 0);
}
void Seihyouki::Motion()
{
	hitBace.CollisionProcess = [&](const Object& o_)
	{
		if (o_.objectTag == "Water")
		{
			switch (((Water&)o_).GetState())
			{
			case Water::State::GAS://ガスの場合
				movetime++;
				if (movetime >= movetime_ice)
				{
					((Water&)o_).SetState(Water::State::LIQUID);
					movetime = 0;
				}
				break;
			case Water::State::LIQUID://液体の場合
				movetime++;
				if (movetime >= movetime_ice)
				{
					((Water&)o_).SetState(Water::State::SOLID);
					movetime = 0;
				}
				break;
			case Water::State::SOLID://個体の場合
				break;
			default:
				break;
			}
		}
	};
	
}
void Seihyouki::CheckHit()	//動いている
{
	hitBace.CollisionProcess = [&](const Object& o_)
	{
		if (o_.objectTag == "Water")
		{
			Motion();
		}
	};
}