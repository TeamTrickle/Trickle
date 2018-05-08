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

void Kanetuki::SetWaterPool(std::vector<Water*>* w) 
{
	water = w;
}

void Kanetuki::Update() 
{
	//‰Á”MŠí‚ÌMotion‹N“®
	for (auto& w : *water)
	{
		if (hitBace.hit(*w))
		{
			toSteam(w);
		}
	}
}
void Kanetuki::toSteam(Water* obj)
{
	if (obj->GetState() == Water::State::LIQUID)
	{
		cout << "ÚG’†" << endl;
		while (true)
		{
			bool flag = false;
			Fire_movetime++;
			if (Fire_movetime >= Fire_time_LIQUID)
			{
				obj->SetState(Water::State::GAS);
				Fire_movetime = 0;
				flag = true;
			}
			if (flag)
			{
				break;
			}
		}
	}
}