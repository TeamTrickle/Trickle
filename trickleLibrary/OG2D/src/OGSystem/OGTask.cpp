#include "OGSystem\OGTask.h"
#include "Task\Task_Title.h"
void OGTK::_myGameInitialize()
{
	//¶¬‚·‚éWindowî•ñ
	OGge->SetWindow(960, 540, "WindowName", false);	
	//OGge->SetWindow(1920, 1080, "Trickel");
	//OGge->SetWindowPos(Vec2(0, 0));
}

void OGTK::StartTaskObject()
{
	//ƒ^ƒXƒN‚Ì‰Šú‰»
	auto TopTask = Title::Create();
}