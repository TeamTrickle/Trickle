#include "Paint.h"
#include "Water\water.h"
Paint::Paint(const Vec2 & pos, const Vec2 & size, const PaintColor & color_)
{
	this->color = new PaintColor(color_);
	this->CreateObject(Cube, pos, size, 0.0f);
	this->objectTag = "Paint";
	this->image = nullptr;
	__super::Init(this->objectTag);
	__super::SetDrawOrder(0.1f);
}
Paint::~Paint()
{
	delete this->color;
}
void Paint::UpDate()
{
	this->WaterHit();
}
void Paint::Render2D()
{
	this->draw = { this->position,this->Scale };
	draw.OffsetSize();
	this->Setsrc();
	if (this->image)
	{
		this->image->Rotate(0);
		this->image->Draw(this->draw, this->src);
	}
}
Paint::SP Paint::Create(const Vec2 & pos, const Vec2 & size, const PaintColor & color_)
{
	Paint::SP to = Paint::SP(new Paint(pos, size, color_));
	if (to)
	{
		to->me = to;
		OGge->SetTaskObject(to);
		return to;
	}
	return nullptr;
}

void Paint::SetTexture(Texture* tex)
{
	this->image = tex;
}
void Paint::Setsrc()
{
	switch (*this->color)
	{
	case PaintColor::Red:
		this->src = { 0,0,256,256 };
		break;
	case PaintColor::Blue:
		this->src = { 256,0,256,256 };
		break;
	case PaintColor::Purple:
		this->src = { 512,0,256,256 };
		break;
	}
	this->src.OffsetSize();
}
bool Paint::WaterHit()
{
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		//当たり判定を行う範囲内か調べる
		if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			//同じ色なら無視する
			if ((*id)->GetColor() != *this->color)
			{
				//当たっているかの判定
				if (this->CubeHit(*(*id)))
				{
					//水の色を変える
					(*id)->SetColor(*this->color);
					//return true;
				}
			}
		}
	}
	return false;
}