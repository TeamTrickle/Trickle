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

void _OGTK::_myGameUpDate()
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
		}
		nowTask = nextTask;
		gameEngine->camera->SetPos(Vec2(0.f, 0.f));
		gameEngine->camera->SetSize(Vec2(gameEngine->window->_widht, gameEngine->window->_height));
		switch (nowTask)
		{
		case Task_Title:
			title.Initialize();
			break;
		case Task_Game:
			game.Initialize();
			break;
		}
	}
	switch (nowTask)
	{
	case Task_Title:
		nextTask = title.Update();
		break;
	case Task_Game:
		nextTask = game.Update();
		break;
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
	}
}