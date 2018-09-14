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
#include "Event\Event.h"

void OGTK::_myGameInitialize()
{
	//生成するWindow情報
	//OGge->SetWindow(960, 540, "Trickle", false);	
	OGge->SetWindow(1920, 1080, "Trickle", true);
	OGge->SetWindowPos(Vec2(0, 0));
	//マウスカーソル不可視
	OGge->SetCursorOn(false);
}

void OGTK::StartTaskObject()
{
	//タスクの初期化
	EventTask ev;
	ev.Load(Event::RESOURCE_LOAD, "./data/event/loadtex.og");
	LogoTask::Create();
}

OGTK::~OGTK()
{
}

void OGTK::UpDate()
{
	if (OGge->in->on(In::D1) && OGge->in->on(In::D2) && OGge->in->on(In::L1) && OGge->in->on(In::R1))
	{
		rm->GetSoundData("titleBGM")->stop();
		OGge->AllKill(false);
		OGge->AllTaskDelete();
		//OGge->in->ResetInputData();
		GameManager::ResetData();
		Title::Create();
		OGge->SetPause(false);
		OGge->AllStop(false);
	}
}