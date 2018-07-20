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

	this->CreateObject(Cube, OGge->camera->GetPos(), Vec2(96, 96), 0.f);
	this->target = target_;

	this->SetDrawOrder(0.9f);

	return true;
}
bool GoalDirection::Finalize()
{
	this->image->Finalize();
	this->flower->Finalize();
	return true;
}
void GoalDirection::SetPos(Vec2& pos)
{
	this->position = pos;
}
void GoalDirection::SetTextrue(Texture* image_ , Texture* flower)
{
	this->image = image_;
	this->flower = flower;
}
void GoalDirection::UpDate()
{
	if (!(std::static_pointer_cast<Goal>(target))->GetClear())
	{
		//ƒS[ƒ‹‚ÌŠp“x‚ð‹‚ß‚Ü‚·
		this->TargetDirecition();
		this->position = this->CameraPosUpDate();
	}
	
}
void GoalDirection::Render2D()
{
	
	if (!(std::static_pointer_cast<Goal>(target))->GetClear())
	{
		if (!this->WindowOuterCheck() || OGge->GetPause())
		{
			{
				Box2D draw = { this->position,this->Scale };
				draw.OffsetSize();
				Box2D src = this->srcbase;
				this->image->Rotate(this->angle);
				this->image->Draw(draw, src);
			}
			{
				Box2D draw = { this->position , this->Scale };
				draw.OffsetSize();
				Box2D src = this->srcflower;
				switch (std::static_pointer_cast<Goal>(target)->GetColor())
				{
				case Paint::PaintColor::Red:
					src.x = 256;
					break;
				case Paint::PaintColor::Blue:
					src.x = 256 * 2;
					break;
				case Paint::PaintColor::Purple:
					src.x = 256 * 3;
					break;
				default:
					break;
				}
				src.OffsetSize();
				this->flower->Draw(draw, src);

			}
			auto player = OGge->GetTask<Player>("Player");
			//Player‚ÆƒS[ƒ‹‚Ì·‚ð‹‚ß‚é
			Vec2 inside = { (target->position.x + target->Scale.x / 2) - (player->position.x + player->Scale.x / 2) , (target->position.y + target->Scale.y / 2) - (player->position.y + player->Scale.y / 2) };
			//•`‰æ”»’è‹éŒ`‚ð¶¬
			Box2D drawchecker = { OGge->camera->GetPos().x + target->Scale.x / 2 , OGge->camera->GetPos().y + target->Scale.y / 2 , OGge->camera->GetSize().x - target->Scale.x , OGge->camera->GetSize().y - target->Scale.y };
			drawchecker.OffsetSize();
			OG::LineHitDraw(&drawchecker);



		}
	}
}
bool GoalDirection::WindowOuterCheck()
{
	/* ƒEƒBƒ“ƒhƒE‚ÆƒS[ƒ‹‚Ì“–‚½‚è”»’è‚ð‚µ‚Ü‚· */
	GameObject windowsize;
	windowsize.CreateObject(Cube, OGge->camera->GetPos(),OGge->camera->GetSize(), 0);
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
		float rad = std::atan2f(player->position.x - (this->target->position.x + this->target->Scale.x / 2), player->position.y - (this->target->position.y + this->target->Scale.y));
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
Vec2 GoalDirection::CameraPosUpDate()
{
	auto player = OGge->GetTask<Player>("Player");
	//Player‚ÆƒS[ƒ‹‚Ì·‚ð‹‚ß‚é
	Vec2 inside = { (target->position.x + target->Scale.x / 2) - (player->position.x + player->Scale.x / 2) , (target->position.y + target->Scale.y / 2) - (player->position.y + player->Scale.y / 2) };
	//•`‰æ”»’è‹éŒ`‚ð¶¬
	Box2D drawchecker = { OGge->camera->GetPos().x + target->Scale.x / 2 , OGge->camera->GetPos().y + target->Scale.y / 2 , OGge->camera->GetSize().x - target->Scale.x , OGge->camera->GetSize().y - target->Scale.y };
	drawchecker.OffsetSize();
	OG::LineHitDraw(&drawchecker);

	float xx = inside.x*inside.x;
	float yy = inside.y*inside.y;
	float r = sqrt(xx + yy);

	float nowx;
	float nowy;
	for (int i = 0; i < r; i++) {
		nowx += xx / r;
		nowy += xx / r;
		Box2D d = { nowx ,nowy, 4.0f, 4.0f };
		d.OffsetSize();
		OG::LineHitDraw(&d);

	}

	return inside;
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
bool GoalDirection::Intersectionhit(Box2D& windowdraw ,Vec2& pos)
{
	auto player = OGge->GetTask<Player>("Player");
	Box2D draw(player->position.x + player->Scale.x / 2, player->position.y + player->Scale.y / 2, pos.x, pos.y);
	draw.OffsetSize();
	//‹éŒ`‚ðƒIƒuƒWƒFƒNƒg¶¬‚·‚é
	GameObject hitobject;
	hitobject.CreateObject(Cube, Vec2(player->position.x + player->Scale.x / 2, player->position.y + player->Scale.y / 2), Vec2(pos.x, pos.y), 0);

	GameObject object;
	object.CreateObject(Cube, Vec2(windowdraw.x, windowdraw.y), Vec2(windowdraw.h, windowdraw.w),0);

	return false;
}
float GoalDirection::OuterProduct(const Vec2& a, const Vec2& b , const Vec2& c , const Vec2& d)
{
	return 0.0f;
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