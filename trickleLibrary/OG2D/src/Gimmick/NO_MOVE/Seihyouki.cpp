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
void Seihyouki::SetWaterPool(std::vector<Water*>*w)
{
	water = w;
}
void Seihyouki::UpDate()
{
	for (auto& w : *water)
	{
		if (w->hit(hitBace))
		{
			toIce(w);
		}
	}
}
void Seihyouki::toIce(Water* obj)
{
	if (obj->GetState() == Water::State::SOLID)
	{
		while (true)
		{
			movetime++;
			if (movetime >= movetime_ice)
			{
				obj->SetState(Water::State::LIQUID);
				movetime = 0;
				break;
			}
		}
	}
	if (obj->GetState() == Water::State::LIQUID)
	{
		while (true)
		{
			movetime++;
			if (movetime >= movetime_ice)
			{
				obj->SetState(Water::State::SOLID);
				movetime = 0;
				break;
			}
		}
	}
}