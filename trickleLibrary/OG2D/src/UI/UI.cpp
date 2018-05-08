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
	appeared = -1;
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
	//		appeared = 0;
	//		//visible = true;
	//		std::cout << "HitUI" << std::endl;
	//	}
	//};
	//Object::CollisionOut = [&](const Object& o_) {
	//	if (o_.objectTag == "Player") {
	//		this->isCollided = false;
	//		//visible = false;
	//		std::cout << "OffUI" << std::endl;
	//	}
	//};
	//Object::CollisionProcess = [&](const Object& o_) {
	//	if (o_.objectTag == "Player") {
	//		this->isCollided = false;
	//		//visible = false;
	//		std::cout << "ProcessUI" << std::endl;
	//	}
	//};

}

void UI::Update() {
	counter++;
	//画像src範囲変更
	if (counter % 30 == 0) {
		index++;
	}
	if (index >= num) {
		index = 0;
	}
	//寿命で死ぬ
	if (counter >= life) {
		active = false;
	}
	//プレイヤが範囲内に入ったら
	if (hit(*player) && appeared == -1) {
		active = true;
		appeared = 0;
	}
	if (!this->hit(*player) && appeared == 0) {
		appeared = 1;
	}
}

void UI::Move(Vec2 pos) {
	this->pos = Vec2(pos.x - 20, pos.y - 140);
}

void UI::Render() {
	Object::LineDraw();
	if (!active || appeared == 1) { return; }
	Box2D draw(pos.x, pos.y, 128.f, 128.f);
	draw.OffsetSize();
	tex.Draw(draw, srcTable[index]);
}

void UI::Finalize() {
	tex.Finalize();
}

//void UI::Appear() {
//	if (isCollided) {
//		active = true;
//	}
//}
//void UI::Vanish() {
//	if (!isCollided) {
//		active = false;
//	}
//}
//bool UI::CheckHitPlayer() {
//	return false;
//}
void UI::SetPlayerPtr(Object* pl) {
	this->player = pl;
}