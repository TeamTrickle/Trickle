#include "OGSystem\OGTask.h"
#include "Task\Task_Title.h"
#include "Task\Task_Game.h"
#include "Task\Task_TitleMovement.h"
#include "Task\Task_Game.h"
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
	*MapNum = 1;
	OGge->camera->SetSize(Vec2(1920, 1080));
	auto ga = Game::Create();
	
}

OGTK::~OGTK()
{
	if (rm->GetTextureData((std::string)"fontui"))
	{
		delete rm->GetTextureData((std::string)"fontui");
		rm->DeleteTexture((std::string)"fontui");
	}
}