#include "Goal.h"


Goal::Goal()
{
}

Goal::~Goal() {}

bool Goal::Initialize() {
	cleared = false;
	this->objectTag = "Goal";
	//テクスチャの読み込み
	tex.TextureCreate("goal.png");
	//オブジェクトの生成
	CreateObject(Objform::Cube, Vec2(28 * 64, 14 * 64), Vec2(64, 64), 0.f);
	return true;
}

bool Goal::Initialize(Vec2& pos) {
	cleared = false;
	this->objectTag = "Goal";
	//テクスチャの読み込み
	tex.TextureCreate("goal.png");
	//オブジェクトの生成
	CreateObject(Objform::Cube, pos, Vec2(64, 64), 0.f);
	return true;
}

void Goal::Update() 
{
	for (int i = 0; i < this->waters.size(); ++i)
	{
		if (this->ClearCheck(*waters[i]))
		{
			this->cleared = true;
		}
	}
}

void Goal::Render() {
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src;
	if (this->cleared) {
		src = Box2D(64, 0, 64, 64);
	}
	else {
		src = Box2D(0, 0, 64, 64);
	}
	src.OffsetSize();
	tex.Draw(draw, src);
}

void Goal::Finalize() 
{
	tex.Finalize();
	this->waters.clear();
}

void Goal::AddWater(Water* o)
{
	this->waters.push_back(o);
}

bool Goal::DeleteWater(Water* o)
{
	for (auto id = this->waters.begin(); id != this->waters.end(); ++id)
	{
		if ((*id) == o)
		{
			this->waters.erase(id);
			return true;
		}
	}
	return false;
}

bool Goal::ClearCheck(Water& o)
{
	if (this->hit(o))
	{
		if (o.GetSituation() == Water::Situation::Normal && o.GetState() == Water::State::LIQUID)
		{
			return true;
		}
	}
	return false;
}