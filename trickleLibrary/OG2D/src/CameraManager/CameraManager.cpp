#include "CameraManager.h"

CameraManager::CameraManager()
{
	this->target = nullptr;
}

CameraManager::~CameraManager()
{
	if (this->target != nullptr)
	{
		this->target = nullptr;
	}
}

void CameraManager::SetObject(GameObject* object)
{
	this->target = object;
}

void CameraManager::SetRange(Box2D& range_)
{
	this->Range = range_;
}

void CameraManager::SetSize(Box2D& size_)
{
	this->Size = size_;
}

void CameraManager::move()
{
	//移動値初期化
	this->est = { 0,0 };
	this->Range = { 100.f,100.f,OGge->camera->GetSize().x - 200.f,OGge->camera->GetSize().y - 200.f };
	//実値の計算
	this->RealRange = { OGge->camera->GetPos().x + this->Range.x,
						OGge->camera->GetPos().y + this->Range.y,
						OGge->camera->GetPos().x + this->Range.x + this->Range.w,
						OGge->camera->GetPos().y + this->Range.y + this->Range.h };
	OG::LineHitDraw(&this->RealRange);
	if (this->target != nullptr)
	{
		this->pretarget = { this->target->position,this->target->Scale };
		//指定範囲外処理
		/*if (this->RealRange.x > this->target->position.x)
		{
			this->est.x += this->target->position.x - this->RealRange.x;
		}
		if (this->RealRange.y > this->target->position.y)
		{
			this->est.y += this->target->position.y - this->RealRange.y;
		}
		if (this->RealRange.w < this->target->position.x + this->target->Scale.x)
		{
			this->est.x += (this->target->position.x + this->target->Scale.x) - this->RealRange.w;
		}
		if (this->RealRange.h < this->target->position.y + this->target->Scale.y)
		{
			this->est.y += (this->target->position.y + this->target->Scale.y) - this->RealRange.h;
		}*/
	}
	//指定範囲外処理
	/*if (this->RealRange.x > this->pretarget.x)
	{
		this->est.x += this->pretarget.x - this->RealRange.x;
	}*/
	/*if (this->RealRange.y > this->pretarget.y)
	{
		this->est.y += this->pretarget.y - this->RealRange.y;
	}*/
	/*if (this->RealRange.w < this->pretarget.x + this->pretarget.w)
	{
		this->est.x += (this->pretarget.x + this->pretarget.w) - this->RealRange.w;
	}*/
	if (this->RealRange.h < this->pretarget.y + this->pretarget.h)
	{
		this->est.y += (this->pretarget.y + this->pretarget.h) - this->RealRange.h;
	}
	//移動値を送る
	OGge->camera->MovePos(this->est);
	//画面外処理
	if (this->Size.x > OGge->camera->GetPos().x)
	{
		OGge->camera->SetPos_x(this->Size.x);
	}
	if (this->Size.y > OGge->camera->GetPos().y)
	{
		OGge->camera->SetPos_y(this->Size.y);
	}
	if (this->Size.w < OGge->camera->GetPos().x + OGge->camera->GetSize().x)
	{
		OGge->camera->SetPos_x(this->Size.w - OGge->camera->GetSize().x);
	}
	if (this->Size.h < OGge->camera->GetPos().y + OGge->camera->GetSize().y)
	{
		OGge->camera->SetPos_y(this->Size.h - OGge->camera->GetSize().y);
	}
}

void CameraManager::DeleteObject()
{
	this->target = nullptr;
}