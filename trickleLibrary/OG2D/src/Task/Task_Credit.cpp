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
	this->timeCnt = 0;
	this->alpha = 0.f;
	return true;
}

void Credit::UpDate()
{
	if (nowMode != Non) {
		++this->timeCnt;
	}

	OGge->camera->SetSize(Vec2(1280, 720));
	auto npc = OGge->GetTask<Chara>("Chara");
	
	if (nowMode == NON) { 
		npc->AutoMove();
		if (!npc->isAutoPlay()) {
			nowMode = MODE1;
		}
	}

	if (nowMode == MODE1) {
		Fade();
	}

	if (nowMode == MODE2) {
		Fade();
	}
	if (nowMode == MODE3) {
		Fade();
	}

	if (nowMode == MODE4) {
		npc->Jump();
		Fade();
	}

	if (nowMode == MODE5) {
		Fade();
	}

	if (nowMode == MODE6) {
		Fade();
	}

	if (nowMode == MODE7) {
		Fade();
		npc->Set(npc->position, Vec2(1500.f, npc->position.y), 30.f);
	}

	if (nowMode == MODE8) {
		npc->AutoMove();
		if (npc->position.x >= 1450) {
			this->Kill();
		}
	}

}

void Credit::Render2D()
{
	//フレーム
	{
		Box2D draw(200, 50, 1000, 585);
		draw.OffsetSize();
		Box2D src = Box2D(0, 0, 1000, 585);
		src.OffsetSize();
		frameTex.Draw(draw, src);
	}
	//名前
	{
		Box2D draw(500, 300, 256, 256);
		draw.OffsetSize();
		Box2D src = Box2D(256 * (nowMode - 1), 0, 256, 256);
		src.OffsetSize();
		Color color(1.f, 1.f, 1.f, alpha);
		nameTex.Draw(draw, src, color);
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

void Credit::Fade()
{
	//フェードイン
	if (this->timeCnt < 20) {
		this->alpha += 0.05f;
	}
	//フェードアウト
	if (this->timeCnt > 60) {
		this->alpha -= 0.05f;
	}
	//次のモードに行く
	if (this->timeCnt > 80) {
		this->alpha = 0;
		this->timeCnt = 0;
		++this->nowMode;
	}

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
