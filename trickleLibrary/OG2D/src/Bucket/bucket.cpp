#include "Bucket\bucket.h"


Bucket::Bucket() {
}

Bucket::~Bucket() {

}

bool Bucket::Initialize() {

	Object::CreateObject(Objform::Cube, Vec2(100.f, 250.f), Vec2(64.f, 64.f), 0.f);
	Object::objectTag = "Bucket";
	Object::CollisionProcess = [&](const Object& o_) {
		if (o_.objectTag == "Water") {
			float waterdrop = ((Water&)o_).waterMove();
			if (capacity < 1.f) {
				capacity += waterdrop;
				((Water&)o_).SetSituation(Water::Situation::Deleteform);
			}
		}
	};

	tex.TextureCreate("bucket.png");
	
	return true;
}

void Bucket::Update() {
}

void Bucket::Render() {
	Box2D draw(this->position, this->Scale);
	draw.OffsetSize();
	Box2D src(GetSpriteCrop());
	src.OffsetSize();
	tex.Draw(draw, src);
}

void Bucket::Finalize() {
	tex.Finalize();
}

Box2D Bucket::GetSpriteCrop() const {
	if (capacity > 0.f)
		return BUCKET_WATER;
	return BUCKET_NOTHING;
}

Water* Bucket::Spill() {
	Water* ret = new Water(this->position);
	ret->position = Vec2(this->position.x + this->Scale.x, this->position.y);
	ret->volume = capacity;
	capacity = 0.f;
	return ret;
}

void Bucket::SetParent(Object* o_) {
	parent = o_;
}

bool Bucket::HasParent() const {
	return parent != nullptr;
}