#include "Kanetuki.h"
using namespace std;
Kanetuki::Kanetuki()
{

}
Kanetuki::~Kanetuki()
{
	w_vec.clear();
}
bool Kanetuki::Create(Vec2 pos, Vec2 scale)
{
	Fire_movetime = 0;
	hitBace.CreateObject(Cube, pos, scale, 0);
	Createflag = false;
	return true;
}
void Kanetuki::CheckHit()
{
	for (auto w : w_vec)
	{
		if (w->hit(hitBace))
		{
			switch (w->GetState())
			{
			case Water::State::GAS:
				break;
			case Water::State::LIQUID:
				cout << "ÚG’†" << endl;
				while (true)
				{
					bool flag = false;
					Fire_movetime++;
					if (Fire_movetime >= Fire_time_LIQUID)
					{
						w->SetState(Water::State::GAS);
						w->position.y = hitBace.position.y - 64;
						Fire_movetime = 0;
						flag = true;
					}
					if (flag)
					{
						break;
					}
				}
				break;
			case Water::State::SOLID:
				Fire_movetime++;
				if (Fire_movetime >= Fire_time_SOLID)
				{
					w->SetState(Water::State::LIQUID);
				}
				Fire_movetime = 0;
				break;
			}
		}
	}
	this->hitBace.LineDraw();
}
void Kanetuki::Set_pointa()
{
	/*hitBace.CollisionProcess = [&](const Object& obj)
	{
		if (obj.objectTag == "Water")
		{
			w_vec.push_back(const_cast<Water*>((Water*)&obj));
		}
	};*/
}
void Kanetuki::Set_pointa(Water* obj)
{
	w_vec.push_back(obj);	
}