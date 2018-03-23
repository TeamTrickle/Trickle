#include "OGSystem\OGTask.h"
void _OGTK::_myGameInitialize()
{
	//ê∂ê¨Ç∑ÇÈWindowèÓïÒ
	_window.createWindow(640, 480, "trickle", false);
	//É^ÉXÉNÇÃèâä˙âª
	nowTask = NON;
	nextTask = Task_Sample;
}

void _OGTK::_myGameUpDate()
{
	if (nowTask != nextTask)
	{
		switch (nowTask)
		{
		case Task_Sample:
			s.Finalize();
			break;
		case Task_Sample2:
			s2.Finalize();
			break;
		}
		nowTask = nextTask;
		switch (nowTask)
		{
		case Task_Sample:
			s.Initialize();
			break;
		case Task_Sample2:
			s2.Initialize();
			break;
		}
	}
	switch (nowTask)
	{
	case Task_Sample:
		nextTask = s.UpDate();
		break;
	case Task_Sample2:
		nextTask = s2.UpDate();
		break;
	}
}

void _OGTK::_myGameRender2D()
{
	switch (nowTask)
	{
	case Task_Sample:
		s.Render2D();
		break;
	case Task_Sample2:
		s2.Render2D();
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
	case Task_Sample:
		s.Finalize();
		break;
	case Task_Sample2:
		s2.Finalize();
		break;
	}
}