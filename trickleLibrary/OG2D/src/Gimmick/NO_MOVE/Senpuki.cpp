#include "Senpuki.h"
using namespace std;

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
		CreateObject(Cube, pos, Vec2(64.0f, 64.0f), 0.0f);
		strength = -3;
		this->WindHitBase.CreateObject(Cube, Vec2(pos.x - (64 * 8), pos.y), Vec2(64 * 8, 64),0.0f);
	}
	else 
	{
		CreateObject(Cube, pos, Vec2(64.0f, 64.0f), 0.0f);
		strength = 3;
		this->WindHitBase.CreateObject(Cube, pos, Vec2(64 * 16, 64), 0.0f);
		//this->WindHitBase.CreateObject(Cube, Vec2(0,0), Vec2(0,0), 0.0f);
	}
}
void Fan::SetWaterPool(Water* w)
{
	this->water.push_back(w);
}
bool Fan::DeleteWaterPool(Water* w)
{
	for (auto id = this->water.begin(); id != this->water.end(); ++id)
	{
		if ((*id) == w)
		{
			this->water.erase(id);
			return true;
		}
	}
	return false;
}
void Fan::UpDate()
{
	for (auto& w : water)
	{
		//当たり判定
		if (this->WindHitBase.hit(*w))
		{//スイッチの状態
			Motion(w);
		}
	}
}
void Fan::Motion(Water* w)
{
	if (active)
	{
		if (w->GetState() == Water::State::GAS)
		{
			//w->position.x += strength; // Left -1 Right 1
			w->MovePos(Vec2(strength, 0));
		}
	}
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
	this->water.clear();
}
void Fan::Render()
{
	Box2D draw(this->position, this->Scale);
	draw.OffsetSize();
	Box2D src(0, 0, 256, 256);
	if (this->dir == Fan::Dir::LEFT)
	{
		int k = src.w;
		src.w = src.x;
		src.x = k;
	}
	this->image->Draw(draw, src);
}
void Fan::SetTexture(Texture* tex)
{
	this->image = tex;
}

void Fan::SetWindRange(Vec2& b)
{
	this->WindHitBase.Scale = b;
}