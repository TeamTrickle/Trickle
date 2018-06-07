#include "Effect.h"

Effect::Effect(const Vec2 & pos, const Vec2 & size, const Vec2 & srcSize, const unsigned int number, const unsigned int time, const unsigned int onetime,const std::string& tag)
{
	this->CreateObject(Cube, pos, size, 0.0f);
	this->objectTag = tag;
	this->animCnt = 0;
	this->anim.time = 0.f;
	this->num = number;
	this->time = time;
	this->one_time = onetime;
	this->oneSize = srcSize;
	this->alpha = 1.0f;
	this->color = { 1.0f,1.0f,1.0f,this->alpha };
	__super::Init(this->objectTag);
	__super::SetDrawOrder(1.0f);
}

Effect::~Effect()
{
}

void Effect::UpDate()
{
	this->animCnt++;
	if (!(this->anim.startPos == this->anim.endPos))
	{
		this->position.x = this->anim.easing_x.sine.InOut(this->anim.easing_x.Time(this->anim.time), this->anim.startPos.x, this->anim.endPos.x, this->anim.time);
		this->position.y = this->anim.easing_y.sine.InOut(this->anim.easing_y.Time(this->anim.time), this->anim.startPos.y, this->anim.endPos.y, this->anim.time);
	}
	if (this->animCnt >= this->time)
	{
		this->Kill();
	}
}

void Effect::Render2D()
{
	this->draw = { this->position,this->Scale };
	this->draw.OffsetSize();
	this->src = { (this->animCnt / this->one_time) % (unsigned int)(this->image->GetTextureSize().x / this->oneSize.x) * this->oneSize.x,(this->animCnt / this->one_time) / (unsigned int)(this->image->GetTextureSize().x / this->oneSize.x) * this->oneSize.y ,this->oneSize.x,this->oneSize.y };
	this->src.OffsetSize();
	this->color.alpha = this->alpha;
	this->image->Draw(this->draw, this->src, this->color);
}

Effect::SP Effect::Create(const Vec2 & pos, const Vec2 & size, const Vec2 & srcSize, const unsigned int number, const unsigned int time, const unsigned int onetime, const std::string& tag, const bool flag)
{
	Effect::SP to = Effect::SP(new Effect(pos, size, srcSize, number, time, onetime, tag));
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
void Effect::Set(const Vec2& start_, const Vec2& end_,const float time_)
{
	this->anim.startPos = start_;
	this->anim.endPos = end_;
	this->anim.time = time_;
	this->anim.endPos -= this->anim.startPos;
	this->anim.easing_x.ResetTime();
	this->anim.easing_y.ResetTime();
}

void Effect::SetTexture(Texture* tex)
{
	this->image = tex;
}

void Effect::Color_a(const float a)
{
	this->alpha = a;
}
