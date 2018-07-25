#include <fstream>
#include "Task_Credit.h"
#include "Chara/Chara.h"
#include "Task/Task_Title.h"
#include "Map/Map.h"
#include "Back/Back.h"

Credit::Credit()
{
	//タスクの検索時に登録した文字列を使用する
	this->taskName = "Credit";	//タスク名決定
	__super::Init(this->taskName);	//タスク名をオブジェクトにも反映
	//描画順の登録
	__super::SetDrawOrder(1.0f);
	//初期化処理
}

Credit::~Credit()
{
	//解放処理
	this->Finalize();
}

bool Credit::Initialize()
{
	//画像生成
	this->frameTex.Create((std::string)"selectframe2.png");
	this->nameTex.Create((std::string)"name.png");
	//背景生成
	auto backImage = Back::Create(std::string("back.png"), 1920, 1080);
	//マップ生成
	Map::Create((std::string) "credit.csv");
	//チャラタスク生成
	auto npc = Chara::Create((std::string)"player.png", Vec2(-120, 64 * 8));
	npc->SetDirection(Chara::Direction::RIGHT); 
	npc->Set(Vec2(-120, 64 * 8), Vec2(64 * 2, 64 * 8), 15.f);
	OGge->camera->SetSize(Vec2(1280, 720));

	this->nowMode = 0;
	this->jumpTimeCnt = 0;
	this->timeCnt = 0;
	this->WAITTIME = 50;
	if (LoadSize())
	{
		SetSize();
	}
	
	
	
	return true;
}

void Credit::UpDate()
{
	OGge->camera->SetSize(Vec2(1280, 720));
	auto npc = OGge->GetTask<Chara>("Chara");
	if (OGge->in->key.down(In::T))
	{
		npc->AutoJump();
	}
	if (nowMode == NON) {
		npc->AutoMoveX();
		if (!npc->isAutoPlay()) {
			this->nowMode = MODE1;
		}
	}

	if (nowMode == MODE1) {
		++timeCnt;
		if (timeCnt >= WAITTIME) {
			npc->SetX(64 * 2, 1700, 30.f);
			this->camera_anim.Set(OGge->camera->GetPos(), Vec2(1600.f, 0.f));
			Next();
		}
	}

	if (nowMode == MODE2) {
		npc->AutoMoveX();
		OGge->camera->SetPos(this->camera_anim.Move(30.f));
		if (!npc->isAutoPlay()) {
			++timeCnt;
			if (timeCnt >= WAITTIME) {
				npc->SetX(1700, 2000, 10.f);
				this->camera_anim.Set(OGge->camera->GetPos(), Vec2(1600.f, 500.f));
				Next();
			}
		}
	}
	if (nowMode == MODE3) {
		++jumpTimeCnt;
		if (jumpTimeCnt > 30 && jumpTimeCnt < 36) {
			npc->AutoJump();
		}
		npc->AutoMoveX();
		OGge->camera->SetPos(this->camera_anim.Move(10.f));
		if (!npc->isAutoPlay()) {
			++timeCnt;
			if (timeCnt >= WAITTIME) {
				npc->SetX(2000, 2300, 30.f);
				this->camera_anim.Set(OGge->camera->GetPos(), Vec2(2200.f, 500.f));
				Next();
			}
		}
	}

	if (nowMode == MODE4) {
		npc->AutoMoveX();
		OGge->camera->SetPos(this->camera_anim.Move(30.f));
		//Next();
	}

	if (nowMode == MODE5) {
		//Next();
	}

	if (nowMode == MODE6) {
		//Next();
	}

	if (nowMode == MODE7) {
		//npc->Set(npc->position, Vec2(1500.f, npc->position.y), 30.f);
		//Next();
	}

	if (nowMode == MODE8) {
		//npc->AutoMove();
		//if (npc->position.x >= 1450) {
			this->Kill();
		//}
	}

}

void Credit::Render2D()
{
	//フレーム
	for (int i = 0; i < FRAME_NUM+1; ++i)
	{
		frameTex.Draw(frame[i].draw, frame[i].src);
	}
}

void Credit::Finalize()
{
	//解放処理
	this->frameTex.Finalize();
	this->nameTex.Finalize();
	auto map = OGge->GetTask<Map>("map");
	auto back = OGge->GetTask<Back>("back");
	if (back)
	{
		back->Kill();
	}
	if (map) { map->Kill(); }
}

void Credit::Next()
{
	//次のモードに行く
	this->timeCnt = 0;
	this->jumpTimeCnt = 0;
	++this->nowMode;
}

Credit::Animation::Animation()
{

}

void Credit::Animation::Set(Vec2& start_, Vec2& end_)
{
	this->StartPos = start_;
	this->EndPos = end_ - start_;
	this->easing_x.ResetTime();
	this->easing_y.ResetTime();
}

Vec2 Credit::Animation::Move()
{
	return Vec2(this->easing_x.quad.InOut(this->easing_x.Time(10), this->StartPos.x, this->EndPos.x, 10), this->easing_y.quad.InOut(this->easing_y.Time(10), this->StartPos.y, this->EndPos.y, 10));
}

Vec2 Credit::Animation::Move(const float time)
{
	return Vec2(this->easing_x.quad.InOut(this->easing_x.Time(time), this->StartPos.x, this->EndPos.x, time), this->easing_y.quad.InOut(this->easing_y.Time(time), this->StartPos.y, this->EndPos.y, time));
}

Vec2 Credit::Animation::Move(const Easing::Name name, const Easing::Mode mode, const float time)
{
	switch (name)
	{
	case Easing::Name::Back:
		break;
	case Easing::Name::Bounce:
		break;
	case Easing::Name::Circ:
		break;
	case Easing::Name::Cubic:
		break;
	case Easing::Name::Elastic:
		break;
	case Easing::Name::Expo:
		break;
	case Easing::Name::Quad:
		break;
	case Easing::Name::Quart:
		break;
	case Easing::Name::Quint:
		break;
	case Easing::Name::Sine:
		break;
	default:
		break;
	}
	return Vec2(this->easing_x.sine.In(this->easing_x.Time(time), this->StartPos.x, this->EndPos.x, 10), this->easing_y.sine.In(this->easing_y.Time(time), this->StartPos.y, this->EndPos.y, time));
}

bool Credit::Animation::isPlay() const
{
	return this->easing_x.isplay() || this->easing_y.isplay() ? true : false;
}

bool Credit::CheckTime(int t)
{
	return this->timeCnt > t ? true : false;
}

Credit::SP Credit::Create(bool flag)
{
	auto to = Credit::SP(new Credit());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize())
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}


bool Credit::LoadSize()
{
	std::ifstream ifs("./data/Credit.txt");

	if (!ifs)
	{
		std::cout << "読み込みエラー" << std::endl;
		return false;
	}
	//読み込んだデータを入れておく変数
	std::string line;
	//改行か終了地点までの文字の文字列をlineにいれる
	std::getline(ifs, line);
	//文字列を操作するための入力class、直接アクセスできる
	std::istringstream _is(line);
	//一字書き込み変数
	std::string text;
	//_isに入っている文字列から','までの文字をtextにいれる
	std::getline(_is, text, '\t');

	for (int i = 0; i < FRAME_NUM+1; ++i) {
		std::string lineText;
		std::getline(ifs, lineText);
		std::istringstream  ss_lt(lineText);
		for (int j = 0; j < 4; ++j)
		{
			std::string  text;
			std::getline(ss_lt, text, '\t');
			if (text == "\r")
			{
				continue;
			}
			(std::stringstream)text >> frame[i].imageSize[j];

		}
	}

	ifs.close();
	return true;
}
void Credit::SetSize()
{
	for (int i = 0; i < FRAME_NUM + 1; ++i) {
		frame[i].draw.x = (float)frame[i].imageSize[frame->DRAW_X];
		frame[i].draw.y = (float)frame[i].imageSize[frame->DRAW_Y];
		frame[i].draw.w = (float)frame[i].imageSize[frame->DRAW_W];
		frame[i].draw.h = (float)frame[i].imageSize[frame->DRAW_H];
		frame[i].draw.OffsetSize();

		frame[i].src.x = 0;
		frame[i].src.y = 0;
		frame[i].src.w = (float)frame[i].imageSize[frame->DRAW_W];
		frame[i].src.h = (float)frame[i].imageSize[frame->DRAW_H];
		frame[i].src.OffsetSize();
	}

}