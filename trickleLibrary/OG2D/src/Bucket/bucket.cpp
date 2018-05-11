#include "Bucket\bucket.h"
Bucket::Bucket() {
	
}

Bucket::Bucket(Vec2& pos) {
	this->position = pos;
}

Bucket::~Bucket() {

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
	//CheckMove(gravity, map, bucket);
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

//バケツから水をこぼす処理 ここには要らなくなる予定
Water* Bucket::Spill() {
	Water* ret = new Water(this->position);
	ret->position = Vec2(this->position.x + this->Scale.x, this->position.y);
	ret->volume = capacity;
	ret->invi = 60;
	capacity = 0.f;
	return ret;
}

void Bucket::SetParent(GameObject* o_) {
	parent = o_;
}

bool Bucket::HasParent() const {
	return parent != nullptr;
}

//-----------------------------------------------------------------------------------------------
//めり込まない処理
void Bucket::CheckMove(Vec2 &e_, Map &map, Bucket &bucket)
{
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

		if (map.MapHitCheck(bucket))
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

		if (map.MapHitCheck(bucket))
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