#include "Gate.h"


Gate::Gate(const Vec2& pos)
{
	this->CreateObject(Cube, pos, Vec2(128, 256), 0.0f);
	this->objectTag = "gate";
	__super::Init(this->objectTag);
	this->image = nullptr;
	auto gates = OGge->GetTasks<Gate>("gate");
	auto id = gates->begin();
	unsigned __int8 i = 0;
	while (id != gates->end())
	{
		++i;
		++id;
	}
	this->ID = i;
}

Gate::~Gate()
{
	this->image = nullptr;
}

void Gate::UpDate()
{

}

void Gate::Render2D()
{
	if (this->image)
	{
		this->draw = { this->position, this->Scale };
		draw.OffsetSize();
		this->src = { 0,0,256,512 };
		this->image->Draw(this->draw, this->src);
	}
}

void Gate::SetTexture(Texture* tex)
{
	this->image = tex;
}

unsigned __int8 Gate::GetID() const
{
	return this->ID;
}

Gate::SP Gate::Create(const Vec2& pos, bool flag)
{
	Gate::SP to = Gate::SP(new Gate(pos));
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		return to;
	}
	return nullptr;
}
Gate::SP Gate::Create(const float posx, const float posy, bool flag)
{
	Gate::SP to = Gate::SP(new Gate(Vec2(posx, posy)));
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		return to;
	}
	return nullptr;
}