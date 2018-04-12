#include "Goal.h"


Goal::Goal()
{
}

Goal::~Goal() {}

bool Goal::Initialize() {
	cleared = false;
	this->objectTag = "Goal";
	//テクスチャの読み込み
	tex.TextureCreate("goal.png");
	//オブジェクトの生成
	CreateObject(Objform::Cube, Vec2(28 * 64, 14 * 64), Vec2(64, 64), 0.f);
	Object::CollisionProcess = [&](const Object& o_) {
		if (o_.objectTag == "Water") {
			if (((Water&)o_).GetSituation() == Water::Situation::Normal && ((Water&)o_).GetState() == Water::State::LIQUID) {
				((Water&)o_).SetSituation(Water::Situation::CreaDelete);
				this->cleared = true;
			}
		}
	};
	return true;
}

void Goal::Update() {

}

void Goal::Render() {
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src;
	if (this->cleared) {
		src = Box2D(64, 0, 64, 64);
	}
	else {
		src = Box2D(0, 0, 64, 64);
	}
	src.OffsetSize();
	tex.Draw(draw, src);
}

void Goal::Finalize() {
	tex.Finalize();
}