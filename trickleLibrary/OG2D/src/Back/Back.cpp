#include "Back.h"

Back::Back(std::string& path, Vec2& size_)
{
	this->backImg.Create(path);
	this->size = size_;
	__super::Init((std::string)"back");
	__super::SetDrawOrder(0.0f);
}

Back::Back(std::string& path, float size_x, float size_y)
{
	this->backImg.Create(path);
	this->size = { size_x,size_y };
	__super::Init((std::string)"back");
	__super::SetDrawOrder(0.0f);
}

Back::Back(std::string& path, int size_x, int size_y)
{
	this->backImg.Create(path);
	this->size = { size_x,size_y };
	__super::Init((std::string)"back");
	__super::SetDrawOrder(0.0f);
}

Back::~Back()
{
	this->backImg.Finalize();
}

void Back::Render2D()
{
	Box2D draw(OGge->camera->GetPos(), this->size);
	draw.OffsetSize();
	Box2D src(0.f, 0.f, this->backImg.GetTextureSize().x, this->backImg.GetTextureSize().y);
	this->backImg.Draw(draw, src);
}

Back::SP Back::Create(std::string& path, Vec2& size_, bool flag)
{
	Back::SP to = Back::SP(new Back(path, size_));
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

Back::SP Back::Create(std::string& path, float x, float y, bool flag)
{
	Back::SP to = Back::SP(new Back(path, x, y));
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

Back::SP Back::Create(std::string& path, int x, int y, bool flag)
{
	Back::SP to = Back::SP(new Back(path, x, y));
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