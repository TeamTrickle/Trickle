#include "Kanetuki.h"
using namespace std;
Kanetuki::Kanetuki()
{
	
}
Kanetuki::~Kanetuki()
{

}
bool Kanetuki::Create(Vec2 pos, Vec2 scale)
{
	Initital = false;
	if(!Initital)
	{
		Fire_movetime = 0;
		hitBace.CreateObject(Cube, pos, scale, 0);
		Initital = true;//‚à‚¤Create‚³‚ê‚È‚¢
		return true;
	}
	return false;
}
void Kanetuki::CheckHit()
{
	for (auto w : w_vec)
	{
		if (w->objectTag == "Water")
		{
			switch (w->GetState())
			{
			case Water::State::GAS:
				Fire_movetime = 0;
				break;
			case Water::State::LIQUID:
				Fire_movetime++;
				if (Fire_movetime >= Fire_time_LIQUID)
				{
					w->SetState(Water::State::GAS);
				}
				break;
			case Water::State::SOLID:
				Fire_movetime++;
				if (Fire_movetime >= Fire_time_SOLID)
				{
					w->SetState(Water::State::LIQUID);
				}
				break;
			default:
				break;
			}
		}
	}
}
void Kanetuki::Set_pointa()
{
	hitBace.CollisionProcess = [&](const Object& obj)
	{
		if (obj.objectTag == "Water")
		{
			w_vec.push_back(const_cast<Water*>(((Water*)&obj)));
		}
	};
}