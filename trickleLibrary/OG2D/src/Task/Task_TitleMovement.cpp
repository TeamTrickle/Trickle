#include "Task_TitleMovement.h"
#include "Back\Back.h"
#include "Chara\Chara.h"
#include "Map\Map.h"


TitleMovement::TitleMovement() {

}

TitleMovement::~TitleMovement() {
	this->Finalize();
}

bool TitleMovement::Initialize() {
	std::cout << "TitleMovement初期化" << std::endl;

	// 背景読み込み
	auto back = Back::Create((std::string)"back.png", 1440, 810);

	// ロゴオブジェクト生成
	logo.CreateObject(Cube, Vec2(400.f, 250.f), Vec2(640.f, 384.f), 0.f);
	logo.Radius = { 1.f, 0.5f };

	// カメラ位置の移動、これ以上の説明が必要韓紙？
	OGge->camera->SetPos(Vec2(OGge->window->GetSize().x / 2, 0.f));
	OGge->camera->SetSize(Vec2(960 / 2, 540 / 2));
	OGge->camera->SetPos(Vec2(500 - (480 / 2), 0));
	this->cm.SetSize(Box2D(Vec2(0, 0), OGge->window->GetSize() * 2));

	// マップを生成（地面用）
	auto map = Map::Create((std::string)"title.csv");
	
	__super::Init((std::string)"titlemovement");
	__super::SetDrawOrder(0.5f);
	return true;
}

void TitleMovement::UpDate() {

}

void TitleMovement::Render2D() {

}

bool TitleMovement::Finalize() {
	return true;
}

TitleMovement::SP TitleMovement::Create(bool flag_) {
	auto to = TitleMovement::SP(new TitleMovement());
	if (to)
	{
		to->me = to;
		if (flag_)
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