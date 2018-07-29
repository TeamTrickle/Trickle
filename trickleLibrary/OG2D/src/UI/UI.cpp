#include "UI.h"
#include "Player\Player.h"

UI::UI() {}

UI::~UI() {
	tex.Finalize();
}

//座標、ファイルパス、画像分割数
bool UI::Initialize(Vec2& renderPos, Box2D& coll, std::string& path, int life, int id, std::function<bool()> appear, std::function<bool()> vanish, int num) {
	this->pos = Vec2(renderPos.x + 128.0f / 2.0f, renderPos.y + 128.0f / 2.0f);
	endPos = renderPos;
	tex.Create(path);
	counter = 0;
	index = 0;
	this->num = num;
	this->life = life;
	active = true;
	appeared = -1;
	maxWH = Vec2(128.0f, 128.0f);
	nowWH = Vec2(0, 0);
	id_ = id;
	this->appear = appear;
	this->vanish = vanish;

	srcTable.resize(num);
	for (int i = 0; i < num; ++i) {
		srcTable[i] = Box2D(256 * i, 0, 256, 256);
		srcTable[i].OffsetSize();
	}
	this->CreateObject(Cube, Vec2(coll.x, coll.y), Vec2(coll.w, coll.h), 0.0f);
	__super::Init((std::string)"UI");
	__super::SetDrawOrder(1.0f);
	return true;
}

void UI::UpDate() {
	auto player = OGge->GetTask<Player>("Player");
	//出現条件
	if (appear) {
		if (appear() && appeared == -1) {
			active = true;
			appeared = 0;
		}
	}
	else {
		if (hit(*player) && appeared == -1) {
			active = true;
			appeared = 0;
		}
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
	//消滅条件
	if (vanish != nullptr) {
		if (vanish() && appeared == 0) {
			appeared = 1;
		}
	}
	else {	//特に指定しない場合はプレイヤ範囲外で消滅
		if (!this->hit(*player) && appeared == 0) {
			appeared = 1;
		}
	}
	//描画範囲変更
	//出現
	if (appeared == 0) {
		if (nowWH.x < maxWH.x) {
			float prex = nowWH.x;
			nowWH.x = easeW.expo.Out(easeW.Time(1), 0.0f, maxWH.x, 1);
			pos.x -= (nowWH.x - prex) / 2.0f;
			if (nowWH.x == prex) {
				nowWH.x = maxWH.x;
				pos.x = endPos.x;
				easeW.Init();
			}
		}
		if (nowWH.y < maxWH.y) {
			float prey = nowWH.y;
			nowWH.y = easeH.bounce.In(easeH.Time(1.3f), 0.0f, maxWH.y, 1.3f);
			pos.y -= (nowWH.y - prey) / 2.0f;
			if (nowWH.y == prey) {
				nowWH.y = maxWH.y;
				pos.y = endPos.y;
				easeH.Init();
			}
		}
	}
	//消滅
	if (appeared == 1) {
		if (nowWH.x > 0) {
			float prex = nowWH.x;
			nowWH.x = easeW.expo.Out(easeW.Time(1), maxWH.x, -maxWH.x, 1);
			pos.x += (prex - nowWH.x) / 2.0f;
			if (nowWH.x == prex) {
				nowWH.x = 0.0f;
				pos.x = 0.0f;
			}
		}
		if (nowWH.y > 0.0f) {
			float prey = nowWH.y;
			nowWH.y = easeH.expo.Out(easeH.Time(1), maxWH.y, -maxWH.y, 1);
			pos.y += (prey - nowWH.y) / 2.0f;
			if (nowWH.y == prey) {
				nowWH.y = 0.0f;
				pos.y = 0.0f;
			}
		}
	}

	if (nowWH.x == 0 && nowWH.y == 0) {
		active = false;
	}
}

//現在未使用
void UI::Move(Vec2 pos) {
	this->pos = Vec2(pos.x - 20, pos.y - 140);
}

void UI::Render2D() {
	if (!active) { return; }
	draw = Box2D(pos.x, pos.y, nowWH.x, nowWH.y);
	draw.OffsetSize();
	tex.Draw(draw, srcTable[index]);
}

bool UI::Finalize() {
	tex.Finalize();
	return true;
}

//使ってない
UI::SP UI::Create(Vec2& pos, Box2D& coll, std::string& path, int life, int num, int id, bool flag_)
{
	auto to = UI::SP(new UI());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos, coll, path, life, id, nullptr, nullptr, num))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}

//UIinfo：Createの引数をまとめたもの
UI::SP UI::Create(UIinfo& info, int id, bool flag_)
{
	Vec2 pos = info.pos;
	Box2D hit = info.hit;
	std::string path = info.path;
	int life = info.life;
	int picNum = info.picNum;
	std::function<bool()> appear = info.appear;
	std::function<bool()> vanish = info.vanish;

	auto to = UI::SP(new UI());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos, hit, path, life, id, appear, vanish, picNum))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}


UImanager::UImanager() {}
UImanager::~UImanager() {
	uiInfo.clear();
}

bool UImanager::Initialize(unsigned short& mapNum) {
	switch (*MapNum) {
	case 1:		//チュートリアル１
		maxNum = 8;
		UIlist_.resize(maxNum);
		uiInfo.resize(maxNum);
		uiInfo[0] = { Vec2(6 * 64, 18 * 64), Box2D(5 * 64,18 * 64,400,300), (std::string)"walkui.png", 150, 4, nullptr, nullptr };
		uiInfo[1] = { Vec2(20 * 64,18 * 64),Box2D(19 * 64,18 * 64,264,300),(std::string)"pusha.png",150,2, nullptr, nullptr };
		uiInfo[2] = { Vec2(25 * 64,16 * 64),Box2D(25 * 64,16 * 64,200,300),(std::string)"pushb.png",100,2, nullptr, std::bind(&UIfunc::getBucket, *uifunc) };
		uiInfo[3] = { Vec2(25 * 64,16 * 64),Box2D(8 * 64,16 * 64,23 * 64,600),(std::string)"arrowleft.png",500,2, nullptr, nullptr };
		uiInfo[4] = { Vec2(6 * 64,18 * 64),Box2D(5 * 64,18 * 64,3 * 64,300),(std::string)"arrowdown.png",500,2, nullptr, std::bind(&UIfunc::getWater, *uifunc) };
		uiInfo[5] = { Vec2(6 * 64,18 * 64),Box2D(6 * 64,16 * 64,13 * 64,600),(std::string)"arrowright.png",500,2,nullptr,nullptr };
		uiInfo[6] = { Vec2(28 * 64,16 * 64),Box2D(20 * 64,16 * 64,8 * 64,400),(std::string)"arrowdown.png",500,2,nullptr,std::bind(&UIfunc::playerPos, *uifunc) };
		uiInfo[7] = { Vec2(29 * 64,16 * 64),Box2D(28 * 64,16 * 64,300,300),(std::string)"pushx.png",500,2, nullptr, std::bind(&UIfunc::spoilWater, *uifunc) };
		UIlist_[0] = UI::Create(uiInfo[0], 0);
		activeID = 0;
		break;
	case 3:		//チュートリアル３
		maxNum = 1;
		UIlist_.resize(maxNum);
		uiInfo.resize(maxNum);
		//uiInfo[0] = { Vec2(17 * 64,14 * 64),Box2D(17 * 64,15 * 64,64,128),(std::string)"pushb.png",500,2,nullptr,std::bind(&UIfunc::getBucket,*uifunc) };
		uiInfo[0] = { Vec2(21 * 64 + 32,14 * 64),Box2D(21 * 64,15 * 64,128,128),(std::string)"pushx.png",500,2,std::bind(&UIfunc::getWater,*uifunc),std::bind(&UIfunc::spoilWater,*uifunc) };
		UIlist_[0] = UI::Create(uiInfo[0], 0);
		activeID = 0;
		break;
	default:
		break;
	}
	return true;
}
void UImanager::UpDate() {
	if (UIlist_.size() == 0) { return; }
	if (UIlist_[activeID] == nullptr) { return; }
	if (!UIlist_[activeID]->active && UIlist_[activeID]->appeared == 1) {
		UIlist_[activeID]->Kill();
		UIlist_[activeID].reset();
		UIlist_[activeID] = nullptr;
		if (activeID < maxNum - 1) {
			activeID++;
			UIlist_[activeID] = UI::Create(uiInfo[activeID], activeID);
		}
	}
}



bool UIfunc::getBucket() {
	auto player = OGge->GetTask<Player>("Player");
	if (player->NowState() == Player::State::BUCKET) {
		return true;
	}
	return false;
}
bool UIfunc::getWater() {
	auto bucket = OGge->GetTasks<Bucket>("bucket");
	for (auto b : *bucket) {
		if (b->GetHold()) {
			if (b->capacity > 0) {
				return true;
			}
		}
	}
	return false;
}
bool UIfunc::Hit(GameObject& me) {
	auto player = OGge->GetTask<Player>("Player");
	if (me.hit(*player)) {
		return true;
	}
	return false;
}
bool UIfunc::NoHit(GameObject& me) {
	auto player = OGge->GetTask<Player>("Player");
	if (!me.hit(*player)) {
		return true;
	}
	return false;
}
bool UIfunc::playerPos() {
	auto player = OGge->GetTask<Player>("Player");
	if (player->position.x >= 28 * 64) {
		return true;
	}
	return false;
}
bool UIfunc::spoilWater() {
	auto bucket = OGge->GetTasks<Bucket>("bucket");
	for (auto b : *bucket) {
		if (b->GetHold()) {
			if (b->capacity == 0) {
				return true;
			}
		}
	}
	return false;
}
extern std::unique_ptr<UIfunc> uifunc(new UIfunc());