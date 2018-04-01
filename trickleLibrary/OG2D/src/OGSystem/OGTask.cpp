#include "OGSystem\OGTask.h"
void _OGTK::_myGameInitialize()
{
	//¶¬‚·‚éWindowî•ñ
	gameEngine->SetWindow(960, 540, "trickle", false);
	//gameEngine->SetWindow(1920, 1080, "trickle", true);
	//ƒ^ƒXƒN‚Ì‰Šú‰»
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
		gameEngine->camera->position = { 0,0 };
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
		nextTask = title.UpDate();
		break;
	case Task_Game:
		nextTask = game.UpDate();
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