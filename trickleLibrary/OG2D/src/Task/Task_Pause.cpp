#include "Task_Pause.h"
#include "Task_Title.h"
#include "Task\StageSelect.h"
#include "Task_Game.h"
#include "Load\LoadLogo.h"
Pause::Pause()
{
	__super::SetDrawOrder(1.0f);
	//サウンドのファイル名格納
	this->cursorsoundname = "cursormove.wav";
	this->dicisionsoundname = "decision.wav";
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

	//サウンドの生成
	//カーソルの移動音
	cursorsound.create(cursorsoundname, false);
	cursorsound.volume(0.7f);
	//決定音
	decisionsound.create(dicisionsoundname, false);

	gearAng = 0;

	imageFlag = true;

	__super::Init((std::string)"pause");
	__super::SetDrawOrder(1.f);		//画像表示順位
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
		if (imageFlag == true) {
			{
				//背景
				{
					Box2D draw(transparentbackPos.x - 16, transparentbackPos.y - 9, 1920.f + 16.f*2.f, 1080.f + 9.f*2.f);
					draw.OffsetSize();
					Box2D src(0, 0, 1280, 720);
					src.OffsetSize();
					texTransparentBack.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, 0.6f));
				}
				//カーソルの表示
				{
					Box2D draw(cursorPos.x, cursorPos.y, 64.0f, 64.0f);
					draw.OffsetSize();
					Box2D src(0, 0, 200, 200);
					src.OffsetSize();
					texCursor.Rotate((float)gearAng);
					texCursor.Draw(draw, src);
				}
				//Restart
				{
					Box2D draw(RestartPos.x, RestartPos.y, 64.f * 7, 64.0f);
					draw.OffsetSize();
					Box2D src(0, 64 * 8, 64 * 7, 64);
					src.OffsetSize();
					rm->GetTextureData((std::string)"fontui")->Draw(draw, src);
				}
				//Return
				{
					Box2D draw(ReturnPos.x, ReturnPos.y, 64.f * 11, 64.0f);
					draw.OffsetSize();
					Box2D src(0, 64 * 9, 64 * 11, 64);
					src.OffsetSize();
					rm->GetTextureData((std::string)"fontui")->Draw(draw, src);
				}
				//stageselect
				{
					Box2D draw(stageselectPos.x, stageselectPos.y, 64.f * 18, 64.0f);
					draw.OffsetSize();
					Box2D src(0, 64 * 7, 64 * 19, 64);
					src.OffsetSize();
					rm->GetTextureData((std::string)"fontui")->Draw(draw, src);
				}
				//選択肢が目立つ処理
				if (cursorPos.y == RestartPos.y) {
					//stageselect
					{
						Box2D draw(stageselectPos.x, stageselectPos.y, 64.f * 18, 64.0f);
						draw.OffsetSize();
						Box2D src(0, 64 * 7, 64 * 19, 64);
						src.OffsetSize();
						rm->GetTextureData((std::string)"fontui")->Draw(draw, src, Color(0.1f, 0.1f, 0.1f, 0.8f));
					}
					//Return
					{
						Box2D draw(ReturnPos.x, ReturnPos.y, 64.f * 11, 64.0f);
						draw.OffsetSize();
						Box2D src(0, 64 * 9, 64 * 11, 64);
						src.OffsetSize();
						rm->GetTextureData((std::string)"fontui")->Draw(draw, src, Color(0.1f, 0.1f, 0.1f, 0.8f));
					}
				}
				if (cursorPos.y == stageselectPos.y) {
					//Restart
					{
						Box2D draw(RestartPos.x, RestartPos.y, 64.f * 7, 64.0f);
						draw.OffsetSize();
						Box2D src(0, 64 * 8, 64 * 7, 64);
						src.OffsetSize();
						rm->GetTextureData((std::string)"fontui")->Draw(draw, src, Color(0.1f, 0.1f, 0.1f, 0.8f));
					}
					//Return
					{
						Box2D draw(ReturnPos.x, ReturnPos.y, 64.f * 11, 64.0f);
						draw.OffsetSize();
						Box2D src(0, 64 * 9, 64 * 11, 64);
						src.OffsetSize();
						rm->GetTextureData((std::string)"fontui")->Draw(draw, src, Color(0.1f, 0.1f, 0.1f, 0.8f));
					}
				}
				if (cursorPos.y == ReturnPos.y) {
					//Restart
					{
						Box2D draw(RestartPos.x, RestartPos.y, 64.f * 7, 64.0f);
						draw.OffsetSize();
						Box2D src(0, 64 * 8, 64 * 7, 64);
						src.OffsetSize();
						rm->GetTextureData((std::string)"fontui")->Draw(draw, src, Color(0.1f, 0.1f, 0.1f, 0.8f));
					}
					//stageselect
					{
						Box2D draw(stageselectPos.x, stageselectPos.y, 64.f * 18, 64.0f);
						draw.OffsetSize();
						Box2D src(0, 64 * 7, 64 * 19, 64);
						src.OffsetSize();
						rm->GetTextureData((std::string)"fontui")->Draw(draw, src, Color(0.1f, 0.1f, 0.1f, 0.8f));
					}
				}
			}
		}
		//カメラが移動すると選択しが透明化処理
		else {
			//カーソルの表示
			{
				Box2D draw(cursorPos.x, cursorPos.y, 64.0f, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 0, 200, 200);
				src.OffsetSize();
				texCursor.Rotate((float)gearAng);
				texCursor.Draw(draw, src, Color(1.f, 1.f, 1.f, 0.1f));
			}
			//Restart
			{
				Box2D draw(RestartPos.x, RestartPos.y, 64.f * 7, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 64 * 8, 64 * 7, 64);
				src.OffsetSize();
				rm->GetTextureData((std::string)"fontui")->Draw(draw, src, Color(0.f, 0.f, 0.f, 0.1f));
			}
			//Return
			{
				Box2D draw(ReturnPos.x, ReturnPos.y, 64.f * 11, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 64 * 9, 64 * 11, 64);
				src.OffsetSize();
				rm->GetTextureData((std::string)"fontui")->Draw(draw, src, Color(0.f, 0.f, 0.f, 0.1f));
			}
			//stageselect
			{
				Box2D draw(stageselectPos.x, stageselectPos.y, 64.f * 18, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 64 * 7, 64 * 19, 64);
				src.OffsetSize();
				rm->GetTextureData((std::string)"fontui")->Draw(draw, src, Color(0.f, 0.f, 0.f, 0.1f));
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
	++gearAng;
	if (gearAng > 360) { gearAng = 0; }
	//選択肢の表示はカメラによって位置が変更
	auto NowCameraPos = OGge->camera->GetPos();
	auto NowCameraSize = OGge->camera->GetSize();
	auto map = OGge->GetTask<Map>("map");
	transparentbackPos = OGge->camera->GetPos();

	//選択しの決定処理
	if (OGge->in->down(In::B2)){
		//サウンドの再生
		decisionsound.play();
		OGge->SetPause(false);
		if (select != Return) {
			//OGge->GetTask<Game>("game")->Kill();
			auto load = Load::Create();
			if (load)
			{
				load->AddDeleteObjectName(OGge->GetTask<Game>("game")->GetTaskName());
				load->ALLTaskUpDateStop();
			}
		}
	}
	if (OGge->in->down(In::D2))
	{
		decisionsound.play();
		OGge->SetPause(false);
	}

	//カメラ移動処理
	float stickSlopeX = OGge->in->axis(In::AXIS_RIGHT_X);
	float stickSlopeY = OGge->in->axis(In::AXIS_RIGHT_Y) * -1.f;

	auto isCameraInStageX = [&](Vec2 eest) ->bool {
		return
			eest.x > 0 &&
			eest.x + NowCameraSize.x < map->mapSize.x * map->DrawSize.x;
	};
	auto isCameraInStageY = [&](Vec2 eest) ->bool {
		return
			eest.y > 0 &&
			eest.y + NowCameraSize.y < map->mapSize.y * map->DrawSize.y;
	};

	Vec2 originCam = OGge->camera->GetPos();

	if (isCameraInStageX(originCam + Vec2(stickSlopeX * 5.f, 0.f))) {
		OGge->camera->MovePos(Vec2(stickSlopeX * 5.f, 0.f));
		imageFlag = false;
	}

	if (isCameraInStageY(originCam + Vec2(0.f, stickSlopeY * 5.f))) {
		OGge->camera->MovePos(Vec2(0.f, stickSlopeY * 5.f));
		imageFlag = false;
	}

	if (InputLeft()) {
		if (NowCameraPos.x > 0) {
			OGge->camera->MovePos(Vec2(-2.5f, 0.0f));
		}
		imageFlag = false;
	}
	else {
		imageFlag = true;
	}

	if (InputRight()) {
		if (NowCameraPos.x + NowCameraSize.x<map->mapSize.x * map->DrawSize.x) {
			OGge->camera->MovePos(Vec2(+2.5f, 0.0f));
		}
		imageFlag = false;
	}

	if (InputUp()) {
		if (NowCameraPos.y > 0) {
			OGge->camera->MovePos(Vec2(0.0f, -2.5f));
		}
		imageFlag = false;
	}
	if (InputDown()) {
		if (NowCameraPos.y + NowCameraSize.y < map->mapSize.y * map->DrawSize.y) {
			OGge->camera->MovePos(Vec2(0.0f, 2.5f));
		}
		imageFlag = false;
	}

	NowCameraPos = OGge->camera->GetPos();
	NowCameraSize = OGge->camera->GetSize();

	//選択し位置
	float NewPos = OGge->camera->GetSize().x + OGge->camera->GetPos().x;
	ReturnPos = Vec2(NewPos - 64 * 12, OGge->camera->GetPos().y + OGge->camera->GetSize().y - 300.f);
	RestartPos = Vec2(NewPos - 64 * 8, OGge->camera->GetPos().y + OGge->camera->GetSize().y - 200.f);
	stageselectPos = Vec2(NewPos - 64 * 19 + 50, OGge->camera->GetPos().y + OGge->camera->GetSize().y - 100.f);

	//矢印の移動
	if (OGge->in->down(Input::CU) || OGge->in->down(In::LU)) {
		selectPos = (selectPos <= 0) ? selectPos : --selectPos;
		//サウンドの再生
		cursorsound.play();
	}
	if (OGge->in->down(Input::CD) || OGge->in->down(In::LD)) {
		selectPos = (selectPos >= 2) ? selectPos : ++selectPos;
		//サウンドの再生
		cursorsound.play();
	}
	Vec2 cPosTable[3] = { Vec2(ReturnPos.x - 80, ReturnPos.y),
		Vec2(RestartPos.x - 80,RestartPos.y),
		Vec2(stageselectPos.x - 80,stageselectPos.y)
	};
	cursorPos = cPosTable[selectPos];
	select = Select::Return;

	//選択し
	if (cursorPos.y == RestartPos.y) {
		select = Restart;
	}
	if (cursorPos.y == stageselectPos.y) {
		select = Stage;
	}
	if (cursorPos.y == ReturnPos.y) {
		select = Return;
	}
}