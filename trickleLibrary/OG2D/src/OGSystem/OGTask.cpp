#include "OGSystem\OGTask.h"
void _OGTK::_myGameInitialize()
{
	//生成するWindow情報
	gameEngine->SetWindow(960, 540, "trickle", false);
	//gameEngine->SetWindow(1920, 1080, "trickle", true);
	//タスクの初期化
	nowTask = NON;
	nextTask = Task_Title;
}

void _OGTK::_myGameUpdate()
{
	if (nowTask != nextTask)
	{
		switch (nowTask)
		{
		case Task_Title:
			title.Finalize();
			break;
		case Task_Game:
			game.Finalize();
			break;
		case Task_Sample:
			//sample.Finalize();
			break;
		case Task_Option:
			option.Finalize();
			break;
		case Task_Ruselt:
			result.Finalize();
			break;
		}
		nowTask = nextTask;
		gameEngine->ChengeTask();
		switch (nowTask)
		{
		case Task_Title:
			title.Initialize();
			break;
		case Task_Game:
			game.Initialize();
			break;
		case Task_Sample:
			//sample.Initialize();
			break;
		case Task_Option:
			option.Initialize();
			break;
		case Task_Ruselt:
			result.Initialize();
			break;
		}
	}
	if (!gameEngine->GetPause()) {
		switch (nowTask)
		{
		case Task_Title:
			nextTask = title.Update();
			break;
		case Task_Game:
			nextTask = game.Update();
			break;
		case Task_Sample:
			//nextTask = sample.UpDate();
			break;
		case Task_Option:
			nextTask = option.Update();
			break;
		case Task_Ruselt:
			nextTask = result.Update();
			break;
		}
	}
	else
	{
		//Pause処理をここに記述
		switch (nowTask)
		{
		case Task_Title:
			break;
		case Task_Game:
			break;
		case Task_Option:
			break;
		case Task_Ruselt:
			break;
		}
	}
}

void _OGTK::_myGameRender2D()
{
	switch (nowTask)
	{
	case Task_Title:
		title.Render2D();
		break;
	case Task_Game:
		game.Render2D();
		break;
	case Task_Option:
		option.Render();
		break;
	case Task_Ruselt:
		result.Render();
		break;
	}
}

void _OGTK::_myGameRender3D()
{

}

void _OGTK::_myGameFinalize()
{
	switch (nowTask)
	{
	case Task_Title:
		title.Finalize();
		break;
	case Task_Game:
		game.Finalize();
		break;
	case Task_Option:
		option.Finalize();
		break;
	case Task_Ruselt:
		result.Finalize();
		break;
	}
}