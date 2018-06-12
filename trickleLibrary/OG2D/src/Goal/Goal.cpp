#include "Goal.h"
#include "Water\water.h"


Goal::Goal(const Vec2& pos)
{
	this->CreateObject(Cube, pos, Vec2(64, 64), 0.0f);
	this->objectTag = "Goal";
	__super::Init(this->objectTag);
	__super::SetDrawOrder(0.5f);
	this->isClear = false;
	this->animCnt = 0;
	this->image = nullptr;
	this->color = Paint::PaintColor::Normal;
}

Goal::~Goal()
{
	this->image = nullptr;
}

void Goal::UpDate()
{
	this->isClear = this->WaterHit();
	if (this->isClear && this->animCnt < 99)
	{
		++this->animCnt;
	}
}

void Goal::Render2D()
{
	if (this->image)
	{
		this->draw = { this->position, this->Scale };
		this->draw.OffsetSize();
		if (this->isClear)
		{
			this->src = { 256 * (int)(animCnt / 10), 256, 256, 284 };
		}
		else
		{
			this->src = { 0,0,256,256 };
		}
		switch (this->color)
		{
		case Paint::PaintColor::Blue:
			this->src.y += 540;
			break;
		case Paint::PaintColor::Red:
			this->src.y += 1080;
			break;
		case Paint::PaintColor::Purple:
			this->src.y += 1620;
			break;
		default:
			break;
		}
		this->src.OffsetSize();
		this->image->Draw(this->draw, this->src);
	}
}

bool Goal::GetClear() const
{
	return this->isClear;
}

void Goal::SetTexture(Texture* tex)
{
	this->image = tex;
}

bool Goal::WaterHit()
{
	this->foot.CreateObject(Cube, Vec2(this->position.x, this->position.y + this->Scale.y - 1.0f), Vec2(this->Scale.x, 1.0f), 0.0f);
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		if ((*id)->GetState() == Water::State::LIQUID)
		{
			if (this->foot.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->foot.hit(*(*id)))
				{
					this->color = (*id)->GetColor();
					(*id)->Kill();
					return true;
				}
			}
		}
	}
	return false;
}

Goal::SP Goal::Create(const Vec2& pos,bool flag)
{
	Goal::SP to = Goal::SP(new Goal(pos));
	if (to)
	{
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		return to;
	}
	return nullptr;
}