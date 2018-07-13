#include "GoalDirectionUI.h"

#include "Player/Player.h"
#include "Goal/Goal.h"

GoalDirection::GoalDirection()
{
	this->taskName = "GoalDirection";	
}
GoalDirection::~GoalDirection()
{
	this->Finalize();
}
bool GoalDirection::Initialize(std::shared_ptr<GameObject> target_)
{
	this->Init(this->taskName);

	this->CreateObject(Cube, OGge->camera->GetPos(), Vec2(192 ,192), 0.f);
	this->target = target_;

	this->drawPattrn = DLeft;
	this->SetDrawOrder(1.0f);

	return true;
}
bool GoalDirection::Finalize()
{
	this->image->Finalize();
	return true;
}
void GoalDirection::SetPos(Vec2& pos)
{
	this->position = pos;
}
void GoalDirection::SetTextrue(Texture* image_)
{
	this->image = image_;
}
void GoalDirection::UpDate()
{
	if (!OGge->GetPause() || !(std::static_pointer_cast<Goal>(target))->GetClear())
	{
		this->CameraPosUpDate();
		//ƒS[ƒ‹‚ÌŠp“x‚ð‹‚ß‚Ü‚·
		this->TargetDirecition();
	}
}
void GoalDirection::Render2D()
{
	if (!OGge->GetPause() || !(std::static_pointer_cast<Goal>(target))->GetClear())
	{
		if (!this->WindowOuterCheck())
		{
			Box2D draw = { this->position,this->Scale };
			draw.OffsetSize();
			Box2D src = this->srcbase;
			this->image->Rotate(this->angle);
			this->image->Draw(draw, src);
		}
	}
}
bool GoalDirection::WindowOuterCheck()
{
	/* ƒEƒBƒ“ƒhƒE‚ÆƒS[ƒ‹‚Ì“–‚½‚è”»’è‚ð‚µ‚Ü‚· */
	GameObject windowsize;
	windowsize.CreateObject(Cube, OGge->camera->GetPos(), Vec2(OGge->camera->GetSize().x - this->target->Scale.x, OGge->camera->GetSize().y - this->target->Scale.y), 0);
	//‚¨‚¨‚Ü‚©‚È“–‚½‚è”»’èŽÀ‘•
	if (!windowsize.IsObjectDistanceCheck(this->target->position, this->target->Scale))
	{
		return false;
	}
	return windowsize.CubeHit(*this->target);
}
//ƒS[ƒ‹‚ÌŠp“x‚ð‹‚ß‚Ü‚·
void GoalDirection::TargetDirecition()
{
	auto player = OGge->GetTask<Player>("Player");

	if (player != nullptr && this->target != nullptr)
	{
		float rad = std::atan2f(player->position.x - this->target->position.x, player->position.y - this->target->position.y);
		this->angle = this->ToDeg(-rad);
	}
}
float GoalDirection::ToDeg(float radian)
{
	float d = (float)(radian * 180.f / PI);
	if (d < 0)
	{
		d += 360.f;
	}
	return d;
}
void GoalDirection::CameraPosUpDate()
{
	switch (this->drawPattrn)
	{
	case DrawPattrn::ULeft:
		this->position = { OGge->camera->GetPos() };
		break;
	case DrawPattrn::URight:
		this->position = { OGge->camera->GetPos().x + OGge->camera->GetSize().x - this->Scale.x, OGge->camera->GetPos().y };
		break;
	case DrawPattrn::UCenter:
		this->position = { OGge->camera->GetPos().x + OGge->camera->GetSize().x / 2 - this->Scale.y, OGge->camera->GetPos().y };
		break;
	case DrawPattrn::CLeft:
		this->position = { OGge->camera->GetPos().x, OGge->camera->GetPos().y + OGge->camera->GetSize().y / 2 - this->Scale.y };
		break;
	case DrawPattrn::CCenter:
		this->position = { OGge->camera->GetPos().x + OGge->camera->GetSize().x / 2 - this->Scale.x, OGge->camera->GetPos().y + OGge->camera->GetSize().y / 2 - this->Scale.y };
		break;
	case DrawPattrn::CRight:
		this->position = { OGge->camera->GetPos().x + OGge->camera->GetSize().x - this->Scale.x, OGge->camera->GetPos().y + OGge->camera->GetSize().y - this->Scale.y };
		break;
	case DrawPattrn::DLeft:
		this->position = { OGge->camera->GetPos().x, OGge->camera->GetPos().y + OGge->camera->GetSize().y - this->Scale.y };
		break;
	case DrawPattrn::DRight:
		this->position = { OGge->camera->GetPos().x + OGge->camera->GetSize().x - this->Scale.x, OGge->camera->GetPos().y + OGge->camera->GetSize().y - this->Scale.y };
		break;
	case DrawPattrn::DCenter:
		this->position = { OGge->camera->GetPos().x + OGge->camera->GetSize().x / 2 - this->Scale.x, OGge->camera->GetPos().y + OGge->camera->GetSize().y / 2 - this->Scale.y };
		break;
	}
}
GoalDirection::SP GoalDirection::Create(std::shared_ptr<GameObject> target, bool flag)
{
	GoalDirection::SP to = GoalDirection::SP(new GoalDirection());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(target))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}






//float direction;
//////‹——£‚ð‹‚ß‚é
//Vec2 inside = {};
//inside = Vec2{ (int)player->position.x - (int)OGge->in->mouse.GetPos().x  , (int)player->position.y - (int)OGge->in->mouse.GetPos().y};
////³‹K‰»
//float sqtr = std::sqrt(inside.x * inside.x + inside.y * inside.y);
//inside = Vec2{ inside.x / sqtr , inside.y / sqtr };
////Šp“x‚ð’²‚×‚é
//Vec2 wegiht = Vec2{ std::cosf(inside.x),-std::sinf(inside.y) };
//float directionY = std::atan2f(wegiht.y, wegiht.x);
////ã‰º”»’è
//if (directionY >= 0)
//{
//	direction += 180;
//}
//else
//{
//	direction = 0;
//}

//this->angle = direction;