#include "water.h"



Water::Water() {

}

Water::~Water() {

}


bool Water::Initialize() {
	this->objectTag = "Water";
	Object::CollisionProcess = [&](const Object& o_) {
		if (o_.objectTag == "Floor") {
			this->isCollided = true;
		}
	};
	CreateObject(Objform::Cube, Vec2(0, 0), Vec2(128, 128), 0.f);
	this->isCollided = false;
	return true;
}

void Water::Update() {
	if (this->isCollided)
	{
		this->position.y = this->position.y;
	}
	else
	{
		this->position.y += 5.0f;
	}
}

void Water::Render() {
	//Box2D src = drawRange[currentState];
	//Box2D draw(0.f, 0.f, src.w, src.h);
	//draw.Offset(Object::position.x, Object::position.y);
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src(0, 0, 128, 128);
	tex.Draw(draw, src);
}

void Water::Finalize() {
	tex.Finalize();
}

void Water::SetState(const State& s_) {
	this->currentState = s_;
}

Water::State Water::GetState() const {
	return currentState;
}