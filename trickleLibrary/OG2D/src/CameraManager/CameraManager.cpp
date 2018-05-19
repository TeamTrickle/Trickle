#include "CameraManager.h"

CameraManager::CameraManager()
{

}

CameraManager::~CameraManager()
{

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