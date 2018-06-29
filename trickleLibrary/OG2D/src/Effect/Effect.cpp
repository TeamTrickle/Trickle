#include "Effect.h"

Effect::Effect(const Vec2 & pos, const Vec2 & size, const Vec2 & srcSize, const unsigned int number, const unsigned int time, const unsigned int onetime, const std::string& tag)
	:MaxFallSpeed(5.f), FallSpeed((9.8f / 60.f / 60.f * 32) * 3), FinSpeed(1.f)
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
	this->angle = 0.f;
	this->oneangle = 0.f;
	this->direction = 0;
	this->color = { 1.0f,1.0f,1.0f,this->alpha };
	this->flag = false;
	this->mode = Mode::Normal;
	this->modealpha = ModeAlpha::NON;
	this->move = nullptr;
	this->Gravity = false;
	__super::Init((std::string)"effect");
	__super::SetDrawOrder(1.0f);
}

Effect::~Effect()
{
	if (this->move)
	{
		delete this->move;
	}
}

void Effect::UpDate()
{
	this->animCnt++;
	if (this->oneangle != 0.0f)
	{
		this->angle += this->oneangle * this->direction;
	}
	if (!(this->anim.startPos == this->anim.endPos))
	{
		this->position.x = this->anim.easing_x.sine.InOut(this->anim.easing_x.Time(this->anim.time), this->anim.startPos.x, this->anim.endPos.x, this->anim.time);
		this->position.y = this->anim.easing_y.sine.InOut(this->anim.easing_y.Time(this->anim.time), this->anim.startPos.y, this->anim.endPos.y, this->anim.time);
	}
	if (this->animCnt >= this->time)
	{
		this->Kill();
	}
	switch (this->mode)
	{
	case Mode::Normal:
		break;
	case Mode::Flash:
		if (this->flag)
		{
			this->alpha += 0.01f;
		}
		else
		{
			this->alpha -= 0.01f;
		}
		if (this->alpha > 1.0f)
		{
			this->flag = false;
		}
		if (this->alpha < 0.0f)
		{
			this->flag = true;
		}
		break;
	case Mode::Decrease:
		this->alpha = 1.0f - ((float)this->animCnt / (float)this->time);
		break;
	case Mode::Expansion:
		if (this->Scale.x < this->maxSize.x || this->Scale.y < this->maxSize.y)
		{
			//float size = 5.0f;
			Vec2 size(this->maxSize.x / this->time, this->maxSize.y / this->time);
			//Šg‘å‰»ˆ—
			this->Scale += size;//Vec2(size, size);
			this->position.x -= size.x / 2.f;
			this->position.y -= size.y / 2.f;
		}
		break;
	case Mode::WindR:
		//if (this->anim.flag)
	{
		this->alpha = 1.0f - ((float)this->animCnt / (float)this->time);
	}
	if (this->Scale.x < this->maxSize.x)
	{
		this->Scale.x += 5.0f;
	}
	else
	{
		if (!this->anim.flag)
		{
			this->Set(this->anim.preS, this->anim.preE, this->anim.time);
			this->anim.flag = true;
		}
	}
	break;
	case Mode::WindL:
		//if (this->anim.flag)
	{
		this->alpha = 1.0f - ((float)this->animCnt / (float)this->time);
	}
	if (this->Scale.x < this->maxSize.x)
	{
		this->Scale.x += 5.0f;
		this->position.x -= 5.0f;
	}
	else
	{
		if (!this->anim.flag)
		{
			this->Set(this->position, this->anim.preE, this->anim.time);
			this->anim.flag = true;
		}
	}
	break;
	case Mode::Down:
		//—Ž‰ºˆ—
		this->Friction();
		this->alpha = 1.0f - ((float)this->animCnt / (float)this->time);
		if (this->move)
		{
			this->position += *this->move;
		}
		break;
	default:
		break;
	}
	switch (this->modealpha)
	{
	case ModeAlpha::NON:
		break;
	case ModeAlpha::FLASH:
		if (this->flag)
		{
			this->alpha += 0.01f;
		}
		else
		{
			this->alpha -= 0.01f;
		}
		if (this->alpha > 1.0f)
		{
			this->flag = false;
		}
		if (this->alpha < 0.0f)
		{
			this->flag = true;
		}
		break;
	case ModeAlpha::UP:
		this->alpha = ((float)this->animCnt / (float)this->time);
		break;
	case ModeAlpha::DOWN:
		this->alpha = 1.0f - ((float)this->animCnt / (float)this->time);
		break;
	}
}

void Effect::Render2D()
{
	this->draw = { this->position,this->Scale };
	this->draw.OffsetSize();
	this->src = { (this->animCnt / this->one_time) % (unsigned int)(this->image->GetTextureSize().x / this->oneSize.x) * this->oneSize.x,(this->animCnt / this->one_time) / (unsigned int)(this->image->GetTextureSize().x / this->oneSize.x) * this->oneSize.y ,this->oneSize.x,this->oneSize.y };
	this->src.OffsetSize();
	this->color.alpha = this->alpha;
	this->image->Rotate(this->angle);
	this->image->Draw(this->draw, this->src, this->color);

}

void Effect::SetMode(const Mode& mode)
{
	this->mode = mode;
}

void Effect::SetMaxSize(const Vec2 &size)
{
	this->maxSize = size;
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
void Effect::Set(const Vec2& start_, const Vec2& end_, const float time_)
{
	this->anim.startPos = start_;
	this->anim.endPos = end_;
	this->anim.time = time_;
	this->anim.endPos -= this->anim.startPos;
	this->anim.easing_x.ResetTime();
	this->anim.easing_y.ResetTime();
}

void Effect::SetWind(const Vec2 & maxSize, const Vec2 & start_, const Vec2 & end_, const Mode& mode, const float time_)
{
	this->anim.preS = start_;
	this->anim.preE = end_;
	this->anim.time = time_;
	this->anim.easing_x.ResetTime();
	this->anim.easing_y.ResetTime();
	this->maxSize = maxSize;
	this->anim.flag = false;
	this->mode = mode;
}

void Effect::SetTexture(Texture* tex)
{
	this->image = tex;
}

void Effect::SetAlphaMode(const ModeAlpha& mode)
{
	this->modealpha = mode;
	switch (this->modealpha)
	{
	case ModeAlpha::DOWN:
		this->color.alpha = 1.0f;
		break;
	case ModeAlpha::UP:
		this->color.alpha = 0.0f;
		break;
	default:
		break;
	}
}

void Effect::Color_a(const float a)
{
	this->alpha = a;
}

void Effect::SetMove(const Vec2& est)
{
	if (this->move)
	{
		delete this->move;
	}
	this->move = new Vec2(est);
	if (this->mode == Mode::Down)
	{
		this->Gravity = true;
	}
}

void Effect::Friction()
{
	if (this->move)
	{
		if (this->move->x > 0)
		{
			this->move->x = std::max(this->move->x - this->FinSpeed, 0.f);
		}
		else
		{
			this->move->x = std::min(this->move->x + this->FinSpeed, 0.f);
		}
		if (this->Gravity)
		{
			this->move->y = std::min(this->move->y + this->FallSpeed, this->MaxFallSpeed);
		}
		else
		{
			this->move->y = 0.0f;
		}
	}
}

void Effect::SetSpeed(float maxfall, float fall, float fin)
{
	this->MaxFallSpeed = maxfall;
	this->FallSpeed = fall;
	this->FinSpeed = fin;
}

void Effect::SetAngle(float f, int i)
{
	this->oneangle = f;
	this->direction = i;
}

//void Effect::SetAlpha(float alpha_)
//{
//	this->alpha = alpha_;
//}