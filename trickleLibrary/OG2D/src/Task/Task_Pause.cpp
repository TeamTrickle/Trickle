#include "Task_Pause.h"
#include "Task_Title.h"
#include "Task\StageSelect.h"
#include "Task_Game.h"
Pause::Pause()
{
	__super::SetDrawOrder(1.0f);
}
//--------------------------------------------------------------------------------------
Pause::~Pause()
{
	this->Finalize();

}
//--------------------------------------------------------------------------------------
bool Pause::Initialize()
{
	//画像読み込み
	texCursor.Create((std::string)"gear2.png");
	texRestart.Create((std::string)"restart.png");
	texReturn.Create((std::string)"return.png");
	texStageSelect.Create((std::string)"StageSelect.png");
	texTransparentBack.Create((std::string)"TransparentBack.png");
	select = Select::Return;

	__super::Init((std::string)"pause");
	__super::SetDrawOrder(1.f);		//画像表示順位
	std::cout << "ポーズ画面初期化" << std::endl;
	return true;
}
//--------------------------------------------------------------------------------------
void Pause::UpDate()
{
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
	texRestart.Finalize();
	texReturn.Finalize();
	texTransparentBack.Finalize();
	texStageSelect.Finalize();

	OGge->SetPause(false);

	switch (select) {
	case Restart:
		{
			/*auto game = OGge->GetTask<Game>("game");
			if (game){
				game->Finalize();
				game->Initialize();
			}*/
		auto game = Game::Create();
		}
	break;
	case Stage:
		{
		/*	auto game = OGge->GetTasks<Game>("game");
			for (auto& g : (*game)) {
				g->Kill();
			}*/
		}
		StageSelect::Create();
		break;
	case Return:
		break;
	}
	return true;
}
//--------------------------------------------------------------------------------------
//ポーズ選択しの表示
void Pause::Pause_draw()
{
	if (OGge->GetPause()) {
		{
			//背景
			{
				Box2D draw(transparentbackPos.x, transparentbackPos.y, 1920.f, 1080.f);
				draw.OffsetSize();
				Box2D src(0, 0, 1280, 720);
				src.OffsetSize();
				texTransparentBack.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, 0.5f));
			}
			//カーソルの表示
			{
				Box2D draw(cursorPos.x, cursorPos.y, 64.0f, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 0, 200, 200);
				src.OffsetSize();
				texCursor.Draw(draw, src);
			}
			//Restart
			{
				Box2D draw(RestartPos.x, RestartPos.y, 64.f*7, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 64*8, 64*7, 64);
				src.OffsetSize();
				rm->GetTextureData((std::string)"fontui")->Draw(draw, src);
			}
			//Return
			{
				Box2D draw(ReturnPos.x, ReturnPos.y, 64.f*11, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 64*9, 64*11, 64);
				src.OffsetSize();
				rm->GetTextureData((std::string)"fontui")->Draw(draw, src);
			}
			//stageselect
			{
				Box2D draw(stageselectPos.x, stageselectPos.y, 64.f*18, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 64*7, 64*19, 64);
				src.OffsetSize();
				rm->GetTextureData((std::string)"fontui")->Draw(draw, src);
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
	//選択肢の表示はカメラによって位置が変更
	auto NowCameraPos = OGge->camera->GetPos();
	auto NowCameraSize = OGge->camera->GetSize();
	auto map = OGge->GetTask<Map>("map");
	float NewPos = NowCameraSize.x + NowCameraPos.x;
	transparentbackPos = OGge->camera->GetPos();

	//選択し位置
	ReturnPos = Vec2(NewPos - 64 * 12, NowCameraPos.y + NowCameraSize.y - 300.f);
	RestartPos = Vec2(NewPos - 64 * 8, NowCameraPos.y + NowCameraSize.y - 200.f);
	stageselectPos = Vec2(NewPos - 64*19 + 50,NowCameraPos.y + NowCameraSize.y - 100.f);

	//矢印の移動
	if (OGge->in->down(Input::CU) || OGge->in->down(In::LU)) {
		selectPos = (selectPos <= 0) ? selectPos : --selectPos;
	}
	if (OGge->in->down(Input::CD) || OGge->in->down(In::LD)) {
		selectPos = (selectPos >= 2) ? selectPos : ++selectPos;
	}
	Vec2 cPosTable[3] = { Vec2(ReturnPos.x - 80, ReturnPos.y)
							,Vec2(stageselectPos.x - 80,stageselectPos.y)
							,Vec2(RestartPos.x - 80,RestartPos.y) };
	cursorPos = cPosTable[selectPos];
	select = Select::Return;

	//選択し
	if (cursorPos.y == RestartPos.y){
		select = Restart;
	}
	if (cursorPos.y == stageselectPos.y){
		select = Stage;
	}
	if (cursorPos.y == ReturnPos.y){
		select = Return;
	}

	//選択しの決定処理
	if (OGge->in->down(In::B2)){
		OGge->SetPause(false);
		if (select != Return) {
			OGge->GetTask<Game>("game")->Kill();
		}
	}

	//カメラ移動処理
	if (InputLeft()) {
		if (NowCameraPos.x > 0) {
			OGge->camera->MovePos(Vec2(-5.0f, 0.0f));
		}
	}
	if (InputRight()) {
		if (NowCameraPos.x + NowCameraSize.x<map->mapSize.x * map->DrawSize.x) {
			OGge->camera->MovePos(Vec2(+5.0f, 0.0f));
		}
	}
	if (InputUp()) {
		if (NowCameraPos.y > 0) {
			OGge->camera->MovePos(Vec2(0.0f, -5.0f));
		}
	}
	if (InputDown()) {
		if (NowCameraPos.y + NowCameraSize.y < map->mapSize.y * map->DrawSize.y) {
			OGge->camera->MovePos(Vec2(0.0f, 5.0f));
		}
	}
}