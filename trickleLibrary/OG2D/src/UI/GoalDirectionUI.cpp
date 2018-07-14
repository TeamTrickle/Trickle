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

	this->CreateObject(Cube, OGge->camera->GetPos(), Vec2(192, 192), 0.f);
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
		//ゴールの角度を求めます
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
		}
	}
}
bool GoalDirection::WindowOuterCheck()
{
	/* ウィンドウとゴールの当たり判定をします */
	GameObject windowsize;
	windowsize.CreateObject(Cube, OGge->camera->GetPos(), Vec2(OGge->camera->GetSize().x - this->target->Scale.x, OGge->camera->GetSize().y - this->target->Scale.y), 0);
	//おおまかな当たり判定実装
	if (!windowsize.IsObjectDistanceCheck(this->target->position, this->target->Scale))
	{
		return false;
	}
	return windowsize.CubeHit(*this->target);

}
//ゴールの角度を求めます
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
Vec2 GoalDirection::CameraPosUpDate()
{
	//座標を調整するための計算
	Vec2 offset = { std::sinf(OG::ToRadian(this->angle)) , -std::cosf(OG::ToRadian(this->angle)) };
	//ウィンドウの真ん中
	Vec2 windowsenter = { (OGge->camera->GetPos().x + OGge->camera->GetSize().x / 2  - this->Scale.x / 2 ), OGge->camera->GetPos().y + OGge->camera->GetSize().y / 2 - this->Scale.y / 2 };
	//ウィンドウサイズ * 角度座標
	windowsenter.x += OGge->window->GetSize().x / 2 * offset.x;
	windowsenter.y += OGge->window->GetSize().y / 2 * offset.y;
	return windowsenter;
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
//////距離を求める
//Vec2 inside = {};
//inside = Vec2{ (int)player->position.x - (int)OGge->in->mouse.GetPos().x  , (int)player->position.y - (int)OGge->in->mouse.GetPos().y};
////正規化
//float sqtr = std::sqrt(inside.x * inside.x + inside.y * inside.y);
//inside = Vec2{ inside.x / sqtr , inside.y / sqtr };
////角度を調べる
//Vec2 wegiht = Vec2{ std::cosf(inside.x),-std::sinf(inside.y) };
//float directionY = std::atan2f(wegiht.y, wegiht.x);
////上下判定
//if (directionY >= 0)
//{
//	direction += 180;
//}
//else
//{
//	direction = 0;
//}

//this->angle = direction;