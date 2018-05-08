#include "Senpuki.h"
using namespace std;

//‰¡“c‚³‚ñ•—
Fan::Fan()
{

}
Fan::Fan(Vec2 pos)
{
	position = pos;
}
Fan::~Fan()
{

}
void Fan::Initialize(Vec2 pos, float r, Fan::Dir d, bool activ) 
{
	position = pos;
	objectTag = "Fan";
	range = r;
	dir = d;
	active = activ;
	if (dir == Fan::Dir::LEFT) 
	{
		CreateObject(Cube, Vec2(position.x - 64.0f*range, position.y), Vec2(64.0f * range, 64.0f), 0.0f);
		strength = -1;
	}
	else 
	{
		CreateObject(Cube, Vec2(position.x + 64.0f, position.y), Vec2(64.0f*range, 64.0f), 0.0f);
		strength = 1;
	}
	Object::CollisionProcess = [&](const Object& o_) 
	{
		if (active) 
		{
			if (o_.objectTag == "Water") 
			{
				if (((Water&)o_).GetSituation() == Water::Situation::Normal && ((Water&)o_).GetState() == Water::State::GAS) 
				{
					const_cast<Object&>(o_).position.x += strength;
				}
			}
		}
	};
}
void Fan::AddSwitch(Switch* swit) 
{
	switches.push_back(swit);
}
void Fan::ChangeState()
{
	active = !active;
}
void Fan::Finalize() 
{
	switches.clear();
	image.Finalize();
}
void Fan::Render(){}