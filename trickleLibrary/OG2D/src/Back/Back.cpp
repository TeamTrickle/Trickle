#include "Back.h"
#include "Map\Map.h"
Back::Back(const std::string& path, Vec2& size_)
{
	this->size = size_;
	this->Init(path);
}

Back::Back(const std::string& path, float size_x, float size_y)
{
	this->size = { size_x,size_y };
	this->Init(path);
}

Back::Back(const std::string& path, int size_x, int size_y)
{
	this->size = { size_x,size_y };
	this->Init(path);
}

void Back::Init(const std::string& path)
{
	this->backImg.Create(path);
	__super::Init((std::string)"back");
	__super::SetDrawOrder(0.0f);
	this->isScroll = false;
	this->mapSize = nullptr;
}

Back::~Back()
{
	this->backImg.Finalize();
	if (this->mapSize)
	{
		delete this->mapSize;
	}
}

void Back::Render2D()
{
	if (this->isScroll)
	{
		Box2D draw(0.f, this->mapSize->y - (this->mapSize->x * 9.f / 16.f), this->mapSize->x, this->mapSize->x * 9.f / 16.f);
		draw.OffsetSize();
		Box2D src(0.f, 0.f, this->backImg.GetTextureSize().x, this->backImg.GetTextureSize().y);
		this->backImg.Draw(draw, src);
	}
	else
	{
		Box2D draw(OGge->camera->GetPos(), this->size);
		draw.OffsetSize();
		Box2D src(0.f, 0.f, this->backImg.GetTextureSize().x, this->backImg.GetTextureSize().y);
		this->backImg.Draw(draw, src);
	}
}

void Back::SetScroll(bool flag)
{
	this->isScroll = flag;
	if (this->isScroll)
	{
		auto map = OGge->GetTask<Map>("map");
		if (map)
		{
			if (this->mapSize)
			{
				delete this->mapSize;
			}
			this->mapSize = new Vec2(map->mapSize);
			*this->mapSize *= 64.f;
		}
	}
}

Back::SP Back::Create(const std::string& path, Vec2& size_, bool flag)
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

Back::SP Back::Create(const std::string& path, float x, float y, bool flag)
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

Back::SP Back::Create(const std::string& path, int x, int y, bool flag)
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