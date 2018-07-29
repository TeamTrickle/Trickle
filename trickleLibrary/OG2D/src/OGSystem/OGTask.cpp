#include "OGSystem\OGTask.h"
#include "Task\Task_Title.h"
#include "Task\Task_Game.h"
#include "Task\Task_TitleMovement.h"
#include "Task\StageSelect.h"
#include "Task\Task_Result.h"
#include "Task\Task_Demo.h"
#include "GameProcessManagement\GameProcessManagement.h"

void OGTK::_myGameInitialize()
{
	//生成するWindow情報
	OGge->SetWindow(960, 540, "WindowName", false);	
	//OGge->SetWindow(1920, 1080, "Trickel", true);
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
	rm->SetTextureData((std::string)"fontui", fontTex);
	Texture* frameTex = new Texture();
	frameTex->Create("frame.png");
	rm->SetTextureData((std::string)"frame.png", frameTex);
	Texture* numberTex = new Texture();
	numberTex->Create("number.png");
	rm->SetTextureData((std::string)"number.png", numberTex);
	//タスクの初期化
	//auto TopTask = Title::Create();
	*MapNum = 10;
	Game::Create();
	//GameManager::ResetData();
}

OGTK::~OGTK()
{
	if (rm->GetTextureData((std::string)"fontui"))
	{
		rm->GetTextureData((std::string)"fontui")->Finalize();
		delete rm->GetTextureData((std::string)"fontui");
		rm->DeleteTexture((std::string)"fontui");
	}
	if (rm->GetTextureData((std::string)"frame.png"))
	{
		rm->GetTextureData((std::string)"frame.png")->Finalize();
		delete rm->GetTextureData((std::string)"frame.png");
		rm->DeleteTexture((std::string)"frame.png");
	}
	if (rm->GetTextureData((std::string)"number.png"))
	{
		rm->GetTextureData((std::string)"number.png")->Finalize();
		delete rm->GetTextureData((std::string)"number.png");
		rm->DeleteTexture((std::string)"number.png");
	}
}