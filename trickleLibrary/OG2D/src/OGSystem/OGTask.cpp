#include "OGSystem\OGTask.h"
#include "Task\Task_Title.h"
#include "Task\Task_Game.h"
#include "Task\Task_TitleMovement.h"
#include "Task\StageSelect.h"
#include "Task\Task_Result.h"
#include "Task\Task_Credit.h"
#include "GameProcessManagement\GameProcessManagement.h"

void OGTK::_myGameInitialize()
{
	//生成するWindow情報
	OGge->SetWindow(960, 540, "WindowName", false);	
//	OGge->SetWindow(1920, 1080, "Trickel", true);
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

	//タスクの初期化
	//auto TopTask = Title::Create();
	*MapNum = 5;
	auto TopTask = Credit::Create();
	//GameManager::ResetData();
}

OGTK::~OGTK()
{
	if (rm->GetTextureData((std::string)"fontui"))
	{
		delete rm->GetTextureData((std::string)"fontui");
		rm->DeleteTexture((std::string)"fontui");
	}
}