#include "OGSystem\OGTask.h"
#include "Task\Task_Title.h"
#include "Task\Task_Game.h"
#include "Task\Task_TitleMovement.h"
#include "Task\StageSelect.h"
#include "Task\Task_Result.h"
#include "Task\Task_Demo.h"
#include "Task\Task_Credit.h"
#include "GameProcessManagement\GameProcessManagement.h"
#include "Task\JecLogo.h"

void OGTK::_myGameInitialize()
{
	//生成するWindow情報
	//OGge->SetWindow(960, 540, "WindowName", false);	
	OGge->SetWindow(1920, 1080, "Trickel", true);
	OGge->SetWindowPos(Vec2(0, 0));
	//マウスカーソル不可視
	OGge->SetCursorOn(false);
}

void OGTK::StartTaskObject()
{
	//使用フォントの読み込み
	Texture* fontTex;
	fontTex = new Texture();
	fontTex->Create("fontui.png");
	rm->SetTextureData("fontui", fontTex);
	Texture* frameTex = new Texture();
	frameTex->Create("frame.png");
	rm->SetTextureData("frame.png", frameTex);
	Texture* numberTex = new Texture();
	numberTex->Create("number.png");
	rm->SetTextureData("number.png", numberTex);
	Texture* BackBrack = new Texture("TransparentBackTitle.png");
	rm->SetTextureData("BrackBackGround", BackBrack);
	Texture* LoadLogo = new Texture("LoadTest.png");
	rm->SetTextureData("LoadLogo", LoadLogo);
	//タスクの初期化
	auto TopTask = LogoTask::Create();
	//*MapNum = 15;
	//Game::Create();
	//GameManager::ResetData();
}

OGTK::~OGTK()
{
	if (rm->GetTextureData("fontui"))
	{
		rm->GetTextureData("fontui")->Finalize();
		delete rm->GetTextureData("fontui");
		rm->DeleteTexture("fontui");
	}
	if (rm->GetTextureData("frame.png"))
	{
		rm->GetTextureData("frame.png")->Finalize();
		delete rm->GetTextureData("frame.png");
		rm->DeleteTexture("frame.png");
	}
	if (rm->GetTextureData("number.png"))
	{
		rm->GetTextureData("number.png")->Finalize();
		delete rm->GetTextureData("number.png");
		rm->DeleteTexture("number.png");
	}
	if (rm->GetTextureData("BrackBackGround"))
	{
		rm->GetTextureData("BrackBackGround")->Finalize();
		delete rm->GetTextureData("BrackBackGround");
		rm->DeleteTexture("BrackBackGround");
	}
	if (rm->GetTextureData("LoadLogo"))
	{
		rm->GetTextureData("LoadLogo")->Finalize();
		delete rm->GetTextureData("LoadLogo");
		rm->DeleteTexture("LoadLogo");
	}
}