#include "Bucket\bucket.h"
#include "Water\water.h"
#include "Map\Map.h"
Bucket::Bucket() {
	
}

Bucket::Bucket(Vec2& pos) {
	this->position = pos;
}

Bucket::~Bucket() {
	this->Finalize();
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{

	}
}

bool Bucket::Initialize(Vec2& pos) {
	this->position = pos;
	gravity = Vec2(0.0f, 0.0f);
	hold = false;
	this->capacity = 0;
	GameObject::CreateObject(Objform::Cube, pos, Vec2(64.f, 64.f), 0.f);
	GameObject::objectTag = "Bucket";

	tex.Create((std::string)"bucket.png");
	
	return true;
}

void Bucket::UpDate() {
	if (hold)
	{
		gravity.y = 0.0f;
	}
	gravity.y += 5.0f;
	if (this->BucketWaterCreate())	//バケツから水を出す処理
	{
		auto water = Water::Create(Vec2(150, 100));
		auto tex = rm->GetTextureData((std::string)"waterTex");
		if (tex)
		{
			water->SetTexture(tex);
		}
		else
		{
			water->Kill();
		}
	}
	//水が当たった時の処理
	this->WaterIsHitCheck();
	
	CheckMove(gravity);
}

void Bucket::Render2D() {
	Box2D draw(this->position, this->Scale);
	draw.OffsetSize();
	Box2D src(GetSpriteCrop());
	src.OffsetSize();
	tex.Draw(draw, src);
}

bool Bucket::Finalize() {
	tex.Finalize();
	return true;
}

Box2D Bucket::GetSpriteCrop() const {
	if (capacity > 0.f)
		return BUCKET_WATER;
	return BUCKET_NOTHING;
}

void Bucket::SetParent(GameObject* o_) {
	parent = o_;
}

bool Bucket::HasParent() const {
	return parent != nullptr;
}

//-----------------------------------------------------------------------------------------------
//めり込まない処理
void Bucket::CheckMove(Vec2 &e_)
{
	auto map = OGge->GetTask<Map>("Map");
	if (!map)
	{
		return;
	}
	//x軸について
	while (e_.x != 0.0f)
	{
		float preX = this->position.x;

		if (e_.x >= 1.0f)
		{
			this->position.x += 1.0f;
			e_.x -= 1.0f;
		}
		else if (e_.x <= -1.0f)
		{
			this->position.x -= 1.0f;
			e_.x += 1.0f;
		}
		else
		{
			this->position.x += e_.x;
			e_.x = 0.0f;
		}

		if (map->MapHitCheck(*this))
		{
			this->position.x = preX;
			break;
		}
	}
	//y軸について
	while (e_.y != 0.0f)
	{
		float preY = this->position.y;

		if (e_.y >= 1.0f)
		{
			this->position.y += 1.0f;
			e_.y -= 1.0f;
		}
		else if (e_.y <= -1.0f)
		{
			this->position.y -= 1.0f;
			e_.y += 1.0f;
		}
		else
		{
			this->position.y += e_.y;
			e_.y = 0.0f;
		}

		if (map->MapHitCheck(*this))
		{
			this->position.y = preY;
			break;
		}
	}
}

bool Bucket::WaterHit(Water* water)
{
	return this->hit(*water);
}

void Bucket::HoldCheck(bool flag)
{
	this->hold = flag;
}


bool Bucket::GetHold() const
{
	return this->hold;
}

bool Bucket::BucketWaterCreate()
{
	return this->hold && OGge->in->down(In::B3) && this->capacity > 0.f;
}

Bucket::SP Bucket::Create(Vec2& pos, bool flag_)
{
	auto to = Bucket::SP(new Bucket(pos));
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}
void Bucket::WaterIsHitCheck()
{
	auto waters = OGge->GetTasks<Water>("water");
	for (int i = 0; i < (*waters).size(); ++i)
	{
		if (this->hit(*(*waters)[i]))
		{
			this->capacity += (*waters)[i]->waterMove();
		}
	}
}