#include "water.h"



Water::Water(Vec2 pos) {
	this->objectTag = "Water";
	Object::CollisionProcess = [&](const Object& o_) {
		if (o_.objectTag == "Floor") {
			this->isCollided = true;
		}
	};
	this->drawRange[Water::State::LIQUID] = Box2D(0, 0, 128, 128);
	this->drawRange[Water::State::GAS] = Box2D(128, 0, 128, 128);
	this->drawRange[Water::State::SOLID] = Box2D(256, 0, 128, 128);
	this->minSize = { 0,0 };
	this->maxSize = { 64,64 };
	this->setTime = 0;
	CreateObject(Objform::Cube, pos, this->minSize, 0.f);
	tex.TextureCreate("watertest.png");
	this->isCollided = false;
	this->nowSituation = Water::Situation::Newfrom;
	this->currentState = Water::State::LIQUID;
}

Water::~Water() {
	tex.Finalize();
}


bool Water::Initialize() {
	this->objectTag = "Water";
	Object::CollisionProcess = [&](const Object& o_) {
		if (o_.objectTag == "Floor") {
			this->isCollided = true;
		}
	};
	CreateObject(Objform::Cube, Vec2(100, 100), Vec2(64, 64), 0.f);
	this->isCollided = false;
	return true;
}

void Water::Update() {
	switch (this->currentState) {
	case Water::State::LIQUID:
		//…ˆ—
		switch (this->nowSituation)
		{
		case Water::Situation::Newfrom:
			this->nowSituation = Water::UpNewform();
			break;
		case Water::Situation::Normal:
			this->nowSituation = Water::UpNormal();
			break;
		case Water::Situation::Deleteform:
			this->nowSituation = Water::UpDeleteform();
			break;
		case Water::Situation::CreaDelete:
			break;
		}
		break;
	case Water::State::GAS:
		//…ö‹Cˆ—
		this->Scale = { this->maxSize.x / 2,this->maxSize.y };
		if (!this->isCollided)
		{
			this->position.y -= 2.f;
		}
		break;
	case Water::State::SOLID:
		//•Xˆ—
		break;
	}
}

Water::Situation Water::UpNewform()
{
	Water::Situation now = this->nowSituation;
	this->setTime++;
	this->Scale.x += 2;
	this->Scale.y += 2;
	this->position.x--;
	if (this->setTime >= this->maxSize.x / 2)
	{
		now = Water::Situation::Normal;
	}
	return now;
}

Water::Situation Water::UpDeleteform()
{
	Water::Situation now = this->nowSituation;
	this->setTime++;
	this->Scale.x -= 2;
	this->Scale.y -= 2;
	this->position.y += 2;
	this->position.x++;
	if (this->setTime >= this->maxSize.x)
	{
		now = Water::Situation::CreaDelete;
	}
	return now;
}

Water::Situation Water::UpNormal()
{
	Water::Situation now = this->nowSituation;
	if (!this->isCollided)
	{
		position.y += 5.0f;
	}
	else
	{
		now = Water::Situation::Deleteform;
	}
	return now;
}

void Water::Render() {
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src = drawRange[currentState];
	src.OffsetSize();
	tex.Draw(draw, src);
}

void Water::Finalize() {
	tex.Finalize();
	//delete this;
}

void Water::SetState(const State& s_) {
	this->currentState = s_;
}

Water::State Water::GetState() const {
	return currentState;
}

void Water::SetSituation(const Situation& s_)
{
	this->nowSituation = s_;
}

Water::Situation Water::GetSituation() const
{
	return this->nowSituation;
}