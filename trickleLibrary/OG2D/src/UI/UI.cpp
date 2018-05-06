#include "UI.h"

UI::UI() {}

UI::~UI() {}

//座標、ファイルパス、画像分割数
void UI::Initialize(Vec2 renderPos, Box2D coll, std::string path, int life, int num) {
	this->pos = renderPos;
	tex.TextureCreate(path);
	counter = 0;
	index = 0;
	this->num = num;
	this->life = life;
	active = false;
	srcTable.resize(num);
	for (int i = 0; i < num; ++i) {
		srcTable[i] = Box2D(256 * i, 0, 256, 256);
		srcTable[i].OffsetSize();
	}
	CreateObject(Cube, Vec2(coll.x, coll.y), Vec2(coll.w, coll.h), 0.0f);
	//objectTag = "UI";
	//this->isCollided = false;
	//Object::CollisionIn = [&](const Object& o_) {
	//	if (o_.objectTag == "Player") {
	//		this->isCollided = true;
	//		active = true;
	//	}
	//};
	//Object::CollisionOut = [&](const Object& o_) {
	//	if (o_.objectTag == "Player") {
	//		this->isCollided = false;
	//		active = false;
	//	}
	//};
}

void UI::Update() {
	counter++;
	if (counter % 30 == 0) {
		index++;
	}
	if (index >= num) {
		index = 0;
	}
	if (counter >= life) {
		active = false;
	}
	if (hit(*player)) {
		active = true;
	}
	else {
		active = false;
	}
}

void UI::Move(Vec2 pos) {
	this->pos = Vec2(pos.x - 20, pos.y - 140);
}

void UI::Render() {
	if (!active) { return; }
	Box2D draw(pos.x, pos.y, 128.f, 128.f);
	draw.OffsetSize();
	tex.Draw(draw, srcTable[index]);
}

void UI::Finalize() {
	tex.Finalize();
}

void UI::Appear() {
	if (isCollided) {
		active = true;
	}
}
void UI::Vanish() {
	if (!isCollided) {
		active = false;
	}
}
bool UI::CheckHitPlayer() {
	return false;
}
void UI::SetPlayerPtr(Object* pl) {
	this->player = pl;
}