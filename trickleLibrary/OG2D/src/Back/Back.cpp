#include "Back.h"
#include "Map\Map.h"
#include <string>
Back::Back(const std::string& path, const Vec2& size_)
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
	Cloud::Create("cloud1.png", 0.5f);
	Cloud::Create("cloud2.png", 1.5f);
	this->backImg.Create(path);
	__super::Init("back");
	__super::SetDrawOrder(0.0f);
	this->isScroll = false;
	this->mapSize = nullptr;
	this->Center = nullptr;
	this->Xsize = nullptr;
	this->Tsize = nullptr;
	this->texPos = nullptr;
}

Back::~Back()
{
	this->backImg.Finalize();
	if (this->mapSize)
	{
		delete this->mapSize;
	}
	if (this->Center)
	{
		delete this->Center;
	}
	if (this->Xsize)
	{
		delete this->Xsize;
	}
	if (this->Tsize)
	{
		delete this->Tsize;
	}
	if (this->texPos)
	{
		delete this->texPos;
	}
}

void Back::UpDate()
{
}

void Back::Render2D()
{
	if (this->isScroll)
	{

		if (this->texPos)
		{
			//画像の描画位置をマップサイズとカメラの位置とカメラのサイズから求める
			*this->texPos = Vec2(OGge->camera->GetPos().x - ((OGge->camera->GetPos().x / *this->Xsize) * *this->Tsize), OGge->camera->GetPos().y - (this->size.y - OGge->camera->GetSize().y) + 320);
		}
		Box2D draw(this->texPos->x, this->texPos->y, this->size.x, this->size.y);
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
			if (this->Center)
			{
				delete this->Center;
			}
			if (this->Xsize)
			{
				delete this->Xsize;
			}
			if (this->Tsize)
			{
				delete this->Tsize;
			}
			if (this->texPos)
			{
				delete this->texPos;
			}
			//マップサイズ取得
			this->mapSize = new Vec2(map->mapSize);
			*this->mapSize *= 64.f;
			//中心取得
			this->Center = new float;
			*this->Center = this->mapSize->x / 2.f;
			//中心にカメラが存在した場合の横のカメラに映らない値を計算
			this->Xsize = new float;
			*this->Xsize = *this->Center - (OGge->camera->GetSize().x / 2.0f);
			//テクスチャのサイズを計算で作成
			this->size.x = this->mapSize->x + OGge->camera->GetSize().x / 4.f;
			this->size.y = this->size.x * 9.f / 16.f;
			//テクスチャのサイズとカメラのサイズの差を計算
			this->Tsize = new float;
			*this->Tsize = (this->size.x - OGge->camera->GetSize().x) / 2.0f;
			//テクスチャの位置を計算で求める
			this->texPos = new Vec2(OGge->camera->GetPos().x - ((OGge->camera->GetPos().x / *this->Xsize) * *this->Tsize), OGge->camera->GetPos().y - (this->size.y - OGge->camera->GetSize().y));
		}
	}
}

bool Back::TexturePositionConfig()
{
	auto map = OGge->GetTask<Map>("map");
	if (!map)
	{
		return false;
	}
	if (this->mapSize)
	{
		delete this->mapSize;
	}
	if (this->Center)
	{
		delete this->Center;
	}
	if (this->Xsize)
	{
		delete this->Xsize;
	}
	if (this->Tsize)
	{
		delete this->Tsize;
	}
	if (this->texPos)
	{
		delete this->texPos;
	}
	//マップサイズ取得
	this->mapSize = new Vec2(map->mapSize);
	*this->mapSize *= 64.f;
	//中心取得
	this->Center = new float;
	*this->Center = this->mapSize->x / 2.f;
	//中心にカメラが存在した場合の横のカメラに映らない値を計算
	this->Xsize = new float;
	*this->Xsize = *this->Center - (OGge->camera->GetSize().x / 2.0f);
	//テクスチャのサイズを計算で作成
	this->size.x = this->mapSize->x + OGge->camera->GetSize().x / 4.f;
	this->size.y = this->size.x * 9.f / 16.f;
	//テクスチャのサイズとカメラのサイズの差を計算
	this->Tsize = new float;
	*this->Tsize = (this->size.x - OGge->camera->GetSize().x) / 2.0f;
	//テクスチャの位置を計算で求める
	this->texPos = new Vec2(OGge->camera->GetPos().x - ((OGge->camera->GetPos().x / *this->Xsize) * *this->Tsize), OGge->camera->GetPos().y - (this->size.y - OGge->camera->GetSize().y));
	return true;
}

Back::SP Back::Create(const std::string& path, const Vec2& size)
{
	Back::SP to = Back::SP(new Back(path, size));
	if (to)
	{
		to->me = to;
		OGge->SetTaskObject(to);
		return to;
	}
	return nullptr;
}

Back::SP Back::Create(const std::string& path, float x, float y)
{
	Back::SP to = Back::SP(new Back(path, x, y));
	if (to)
	{
		to->me = to;
		OGge->SetTaskObject(to);
		return to;
	}
	return nullptr;
}

Back::SP Back::Create(const std::string& path, int x, int y)
{
	Back::SP to = Back::SP(new Back(path, x, y));
	if (to)
	{
		to->me = to;
		OGge->SetTaskObject(to);
		return to;
	}
	return nullptr;
}


Cloud::Cloud(const std::string & path, float speed) {
}

Cloud::~Cloud() {}

std::shared_ptr<Cloud> Cloud::Create(const std::string & path, float speed)
{
	auto obj = std::shared_ptr<Cloud>(new Cloud(path, speed));
	if (obj) {
		obj->me = obj;
		obj->Initialize(path, speed);
		std::shared_ptr<Cloud> o(obj);
		OGge->SetTaskObject(o);
		return o;
	}
	return nullptr;
}

void Cloud::Initialize(const std::string & path, float speed) {
	cloudImg.Create(path);
	cloudPos[0] = Vec2(0, 0);
	cloudPos[1] = Vec2(-1920, 0);
	this->speed = speed;
	SetDrawOrder(0.01f);
	Init("cloud");
}

void Cloud::UpDate() {
	for (int i = 0; i < 2; ++i) {
		cloudPos[i].x += speed;
		if (cloudPos[i].x >= 1920) {
			cloudPos[i].x = -1920;
		}
	}
}

void Cloud::Render2D() {
	for (int i = 0; i < 2; ++i) {
		Box2D draw(cloudPos[i].x, cloudPos[i].y, 1920.f, 1080.f);
		draw.OffsetSize();
		Box2D src(0, 0, 1280, 720);
		cloudImg.Draw(draw, src);
	}
}