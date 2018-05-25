#include "Task_Pause.h"
#include "Task_Title.h"
#include "Task\StageSelect.h"
#include "Task_Game.h"
Pause::Pause()
{
	__super::SetDrawOrder(1.f);
}
//--------------------------------------------------------------------------------------
Pause::~Pause()
{
	this->Finalize();
}
//--------------------------------------------------------------------------------------
bool Pause::Initialize()
{
	//ポーズ判定
	PauseFlg = false;
	//画像読み込み
	texCursor.Create((std::string)"Collision.png");
	texTitle.Create((std::string)"titleTx.png");
	texRuselt.Create((std::string)"Ruselt.png");
	texStageSelect.Create((std::string)"StageSelect.png");
	texTransparentBack.Create((std::string)"TransparentBack.png");

	this->nextTaskCheck = 0;
	__super::Init((std::string)"pause");
	__super::SetDrawOrder(1.f);		//画像表示順位
	std::cout << "ポーズ画面初期化" << std::endl;
	return true;
}
//--------------------------------------------------------------------------------------
void Pause::UpDate()
{
	//ポーズへの移動
	if (OGge->in->key.down(In::G)) {
		OGge->SetPause(true);
		PauseFlg = true;
	}
}
//--------------------------------------------------------------------------------------
void Pause::Render2D()
{
	//ポーズ選択しの表示
	Pause_draw();

}
//--------------------------------------------------------------------------------------
bool Pause::Finalize()
{
	std::cout << "Pause解放" << std::endl;

	//使用画像の解放
	texCursor.Finalize();
	texTitle.Finalize();
	texRuselt.Finalize();
	texTransparentBack.Finalize();
	texStageSelect.Finalize();

	auto gameTask = OGge->GetTask<Game>("game");
	if (gameTask) gameTask->Kill();

	auto titleTask = OGge->GetTask<Title>("title");
	if (titleTask) titleTask->Kill();

	if (this->select != Select::Ruselt) {
		auto game = OGge->GetTask<Game>("game");
		if (game) {
			game->Kill();
		}
	}

	switch (select) {
	case ToTitle:
		Title::Create();
		break;
	case Stage:
		StageSelect::Create();
		break;
	case Ruselt:
		break;
	}
	return true;
}
//--------------------------------------------------------------------------------------
//ポーズ選択しの表示
void Pause::Pause_draw()
{
	if (PauseFlg == true) {
		{
			//背景
			{
				Box2D draw(transparentbackPos.x, transparentbackPos.y, 1280.0f, 720.0f);
				draw.OffsetSize();
				Box2D src(0, 0, 1280, 720);
				src.OffsetSize();
				texTransparentBack.Draw(draw, src);
			}
			//カーソルの表示
			{
				//ゲームスタート
				Box2D draw(cursorPos.x, cursorPos.y, 64.0f, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 0, 128, 128);
				src.OffsetSize();
				texCursor.Draw(draw, src);
			}
			//Title
			{
				Box2D draw(titlePos.x, titlePos.y, 256.0f, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 0, 256, 64);
				src.OffsetSize();
				texTitle.Draw(draw, src);
			}
			//ruselt
			{
				Box2D draw(ruseltPos.x, ruseltPos.y, 256.0f, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 0, 256, 64);
				src.OffsetSize();
				texRuselt.Draw(draw, src);
			}
			//stageselect
			{
				Box2D draw(stageselectPos.x, stageselectPos.y, 256.0f, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 0, 256, 64);
				src.OffsetSize();
				texStageSelect.Draw(draw, src);
			}

		}
	}
}
//--------------------------------------------------------------------------------------
Pause::SP Pause::Create(bool flag_)
{
	auto to = Pause::SP(new Pause());
	if (to)
	{
		to->me = to;
		if (flag_) {
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize()) {
			to->Kill();
		}
		return to;
	}
	return nullptr;
}
//--------------------------------------------------------------------------------------
void Pause::PauseUpDate()
{
	//デバッグ用
	//std::cout << "Puase" << std::endl;
	//ポーズ画面の解除
	if (OGge->in->key.down(In::G)) {
		OGge->SetPause(false);
		PauseFlg = false;
	}

	//選択肢の表示はカメラによって位置が変更
	auto NowCameraPos = OGge->camera->GetPos();
	transparentbackPos = Vec2(NowCameraPos.x, NowCameraPos.y);
	titlePos = Vec2(NowCameraPos.x + 700.0f, NowCameraPos.y + 50.0f);
	ruseltPos = Vec2(NowCameraPos.x + 700.0f, NowCameraPos.y + 250.0f);
	stageselectPos = Vec2(NowCameraPos.x + 700.0f, NowCameraPos.y + 150.0f);
	//矢印の移動
	if (OGge->in->key.down(In::UP)) {
		selectPos = (selectPos <= 0) ? selectPos : --selectPos;
	}
	if (OGge->in->key.down(In::DOWN)) {
		selectPos = (selectPos >= 2) ? selectPos : ++selectPos;
	}
	cursorPos = Vec2(NowCameraPos.x + 600.0f, NowCameraPos.y + 50.0f + (100.f * selectPos));
	select = Select::Ruselt;
	//選択し
	if (cursorPos.y == titlePos.y)
	{
		select = ToTitle;
	}
	if (cursorPos.y == stageselectPos.y)
	{
		select = Stage;
	}
	if (cursorPos.y == ruseltPos.y)
	{
		select = Ruselt;
	}
	//選択しの決定処理
	if (OGge->in->down(In::B2))
	{
		OGge->SetPause(false);
		PauseFlg = false;
		if (select != Ruselt) {
			this->Kill();
		}
	}
}