#include "UI.h"
#include "Player\Player.h"

UI::UI() {}

UI::~UI() {
	//tex.Finalize();
}

//座標、ファイルパス、画像分割数
bool UI::Initialize(Vec2& renderPos, Box2D& coll, std::string& path, int life, int id, UImanager* manager, int num) {
	this->pos = renderPos;
	tex.Create(path);
	counter = 0;
	index = 0;
	this->num = num;
	this->life = life;
	active = true;
	appeared = -1;
	id_ = id;

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
	//プレイヤが範囲内に入ったら
	auto player = OGge->GetTask<Player>("Player");
	if (hit(*player) && appeared == -1) {
		active = true;
		appeared = 0;
	}
	if (!active) { return; }
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
		//auto next = new UI();
		//next->Initialize()
		//manager->AddUI(new UI());
		//this->Kill();
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
	//if (!active || appeared == 1) { return; }
	Box2D draw(pos.x, pos.y, 128.f, 128.f);
	draw.OffsetSize();
	tex.Draw(draw, srcTable[index]);
}

bool UI::Finalize() {
	tex.Finalize();
	return false;
}

bool UI::CreateNext(UIinfo& info) {


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

UI::SP UI::Create(Vec2& pos, Box2D& coll, std::string& path, int life, int num, int id, UImanager* manager, bool flag_)
{
	auto to = UI::SP(new UI());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos, coll, path, life, id, manager, num))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}

UI::SP UI::Create(UIinfo& info, int id, UImanager* manager, bool flag_)
{
	Vec2 pos = info.pos;
	Box2D hit = info.hit;
	std::string path = info.path;
	int life = info.life;
	int picNum = info.picNum;

	auto to = UI::SP(new UI());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos, hit, path, life, id, manager, picNum))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}


UImanager::UImanager(){}
UImanager::~UImanager(){
	uiInfo.clear();
	//if (!UIlist_.empty()) {
	//	for (auto ui : UIlist_) {

	//	}
	//}
}

bool UImanager::Initialize(unsigned short& mapNum) {
	switch (*MapNum) {
	case 1:
		maxNum = 7;
		UIlist_.resize(maxNum);
		uiInfo.resize(maxNum);
		uiInfo[0] = { Vec2(6 * 64, 18 * 64), Box2D(200, 300, 200, 300), (std::string)"walkui.png", 150, 4 };
		uiInfo[1] = { Vec2(20 * 64,18 * 64),Box2D(1200,300,200,300),(std::string)"pusha.png",150,2 };
		uiInfo[2] = { Vec2(25 * 64,16 * 64),Box2D(1500,200,200,300),(std::string)"pushb.png",100,2 };
		uiInfo[3] = { Vec2(25 * 64,16 * 64),Box2D(200,200,1000,300),(std::string)"arrowleft.png",500,2 };
		uiInfo[4] = { Vec2(6 * 64,18 * 64),Box2D(200,300,1000,300),(std::string)"arrowright.png",500,2 };
		uiInfo[5] = { Vec2(28 * 64,16 * 64),Box2D(1700,200,200,300),(std::string)"arrowdown.png",500,2 };
		uiInfo[6] = { Vec2(29 * 64,16 * 64),Box2D(1700,200,300,300),(std::string)"pushx.png",500,2 };
		//for (int i = 0; i < maxNum; ++i) {
		//	UIlist_.push_back(UI::Create(uiInfo[i], i, this));
		//}
		UIlist_[0] = UI::Create(uiInfo[0], 0, this);
		activeID = 0;
		break;
	case 3:
		break;
	default:
		break;
	}
	return true;
}
void UImanager::UpDate() {
	//if (activeID >= maxNum - 1) { return; }
	if (UIlist_.size() == 0) { return; }
	if (UIlist_[activeID] == nullptr) { return; }
	if (!UIlist_[activeID]->active) {
		UIlist_[activeID]->Kill();
		//UIlist_[activeID].reset();
		UIlist_[activeID] = nullptr;
		if (activeID < maxNum - 1) {
			activeID++;
			UIlist_[activeID] = UI::Create(uiInfo[activeID], activeID, this);
		}
		else {
			//UIlist_[activeID]->Kill();
			//UIlist_[activeID].reset();
			Finalize();
		}
	}
}
bool UImanager::AddUI(UI* next) {
	//UIlist_.push_back(next);
	//return true;
	return false;
}
bool UImanager::Finalize() {
	return true;
}