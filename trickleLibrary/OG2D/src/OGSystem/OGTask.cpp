#include "OGSystem\OGTask.h"
void OGTK::_myGameInitialize()
{
	//¶¬‚·‚éWindowî•ñ
	OGge->SetWindow(960, 540, "WindowName", false);	
	OGge->window->createWindow(50, 50, "", false, Vec2(0, 0));
}

void OGTK::StartTaskObject()
{
	//ƒ^ƒXƒN‚Ì‰Šú‰»
	auto TopTask = Sample::Create(true);
}