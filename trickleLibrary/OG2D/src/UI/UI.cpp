#include "UI.h"
#include "Player\Player.h"

UI::UI() {}

UI::~UI() {}

//座標、ファイルパス、画像分割数
bool UI::Initialize(Vec2& renderPos, Box2D& coll, std::string& path, int life, int num) {
	this->pos = renderPos;
	tex.Create(path);
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
	this->CreateObject(Cube, Vec2(coll.x, coll.y), Vec2(coll.w, coll.h), 0.0f);
	__super::Init((std::string)"UI");
	return true;
}

void UI::UpDate() {
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
	auto player = OGge->GetTask<Player>("Player");
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

void UI::Render2D() {
	GameObject::LineDraw();
	if (!active || appeared == 1) { return; }
	Box2D draw(pos.x, pos.y, 128.f, 128.f);
	draw.OffsetSize();
	tex.Draw(draw, srcTable[index]);
}

bool UI::Finalize() {
	tex.Finalize();
	return false;
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

UI::SP UI::Create(Vec2& pos, Box2D& coll, std::string& path, int life, int num,bool flag_)
{
	auto to = UI::SP(new UI());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos, coll, path, life, num))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}