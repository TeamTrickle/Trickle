#include "Task_Pause.h"
#include "Task_Title.h"
#include "Task\StageSelect.h"
#include "Task_Game.h"
Pause::Pause()
{
	__super::SetDrawOrder(1.f);
}

Pause::~Pause()
{
	this->Finalize();
}

bool Pause::Initialize()
{
	PauseFlg = false;

	transparentbackPos = Vec2(0.0f, 0.0f);

	texCursor.Create((std::string)"Collision.png");
	texTitle.Create((std::string)"titleTx.png");
	texRuselt.Create((std::string)"Ruselt.png");
	texStageSelect.Create((std::string)"StageSelect.png");
	texTransparentBack.Create((std::string)"TransparentBack.png");

	this->nextTaskCheck = 0;
	__super::Init((std::string)"pause");
	__super::SetDrawOrder(1.f);
	std::cout << "ポーズ画面初期化" << std::endl;
	return true;
}

void Pause::UpDate()
{
	//ポーズへの移動
	if (OGge->in->key.down(In::G)) { 
		OGge->SetPause(true);
			PauseFlg = true;
	}
}

void Pause::Render2D()
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

bool Pause::Finalize()
{
	std::cout << "Pause解放" << std::endl;

	//使用画像の解放
	texCursor.Finalize();
	texTitle.Finalize();
	texRuselt.Finalize();
	texTransparentBack.Finalize();
	texStageSelect.Finalize();

	//if (this->GetNextTask() && !OGge->GetDeleteEngine())
	//{
	//	OGge->ChengeTask();
	//	switch (sex)
	//	{
	//	case Title:
	//		Title::Create();
	//		break;
	//	case StageSelect:
	//	{
	//		StageSelect::Create();
	//	}
	//	break;
	//	//case Pause:
	//	//{
	//	//	auto option = Option::Create();
	//	//}
	//	//break;
	//	default:
	//		break;
	//	}
	//}

	auto gameTask = OGge->GetTask<Game>("game");
	if (gameTask) gameTask->Kill();

	auto titleTask = OGge->GetTask<Title>("title");
	if (titleTask) titleTask->Kill();

	if (this->select != Select::Ruselt)
	{
		auto game = OGge->GetTask<Game>("game");
		if (game)
		{
			game->Kill();
		}
	}
	
	switch (select) {
	case ToTitle: {
		Title::Create();
		
	}
				  //Title::Create();
				  break;
	case Stage:
		StageSelect::Create();
		break;
	case Ruselt:

		break;
	}
	return true;
}

//void Pause::CursorMove()
//{
//	if (cursorPos.y > startPos.y)
//	{
//		if (OGge->in->down(In::CU))
//		{
//			cursorPos.y -= 100.0f;
//		}
//	}
//	if (cursorPos.y < closePos.y)
//	{
//		if (OGge->in->down(In::CD))
//		{
//			cursorPos.y += 100.0f;
//		}
//	}
//
//	if (cursorPos.y == startPos.y)
//	{
//		state = Start;
//	}
//	if (cursorPos.y == pausePos.y)
//	{
//		state = Pause;
//	}
//	if (cursorPos.y == closePos.y)
//	{
//		state = Close;
//	}
//}

Pause::SP Pause::Create(bool flag_)
{
	auto to = Pause::SP(new Pause());
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
//
void Pause::PauseUpDate() 
{ 
	//this->UpDate();
	std::cout << "Puase" << std::endl;
	//ポーズ画面の解除
	if (OGge->in->key.down(In::G)) {
		OGge->SetPause(false); 
			PauseFlg = false;
			//this->Kill();
	}
	//矢印の移動
	auto NowCameraPos = OGge->camera->GetPos();
	titlePos = Vec2(NowCameraPos.x + 700.0f, NowCameraPos.y + 50.0f);
	ruseltPos = Vec2(NowCameraPos.x + 700.0f, NowCameraPos.y + 250.0f);
	stageselectPos = Vec2(NowCameraPos.x + 700.0f, NowCameraPos.y + 150.0f);

	if (OGge->in->key.down(In::UP))		sex = (sex <= 0) ? sex : --sex;
	if (OGge->in->key.down(In::DOWN))	sex = (sex >= 2) ? sex : ++sex;
	cursorPos = Vec2(NowCameraPos.x + 600.0f, NowCameraPos.y + 50.0f + (100.f * sex));
	select = Select::Ruselt;
	if (cursorPos.y == titlePos.y)
	{
		select = ToTitle;
	}
	if (cursorPos.y == stageselectPos.y)
	{
		select = Stage;
	}
	//決定
	if (OGge->in->down(In::B2))
	{
		OGge->SetPause(false);
		this->Kill();
	}
}