#include "OGSystem\OGTask.h"
void OGTK::_myGameInitialize()
{
	//生成するWindow情報
	OGge->SetWindow(960, 540, "WindowName", false);	
	OGge->window->createWindow(50, 50, "", false, Vec2(0, 0));
}

void OGTK::StartTaskObject()
{
	//タスクの初期化
	auto TopTask = Sample::Create(true);
}