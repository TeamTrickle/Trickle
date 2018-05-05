#include "StageSelect.h"

void StageSelect::Initialize()
{

}

TaskFlag StageSelect::UpDate()
{
	TaskFlag nowTask = Task_StageSelect;
	if (gameEngine->in.key.down(In::ENTER))
	{
		*MapNum = 0;
		nowTask = Task_Game;
	}
	return nowTask;
}

void StageSelect::Render()
{

}

void StageSelect::Finalize()
{

}