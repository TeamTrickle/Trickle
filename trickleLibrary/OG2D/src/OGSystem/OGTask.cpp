#include "OGSystem\OGTask.h"
#include "Task\Task_Title.h"
#include "Task\Task_Game.h"
#include "Task\Task_TitleMovement.h"
#include "Task\StageSelect.h"
#include "Task\Task_Result.h"

void OGTK::_myGameInitialize()
{
	//生成するWindow情報
	OGge->SetWindow(960, 540, "WindowName", false);	
	//OGge->SetWindow(1920, 1080, "Trickel", true);
	//OGge->SetWindowPos(Vec2(0, 0));
	//マウスカーソル不可視
	OGge->SetCursorOn(false);
}

void OGTK::StartTaskObject()
{
	//タスクの初期化
	//auto TopTask = Title::Create();
	auto task = StageSelect::Create();
	OGge->camera->SetSize(Vec2(1920, 1080));
}

OGTK::~OGTK()
{
	if (rm->GetTextureData((std::string)"fontui"))
	{
		delete rm->GetTextureData((std::string)"fontui");
		rm->DeleteTexture((std::string)"fontui");
	}
}