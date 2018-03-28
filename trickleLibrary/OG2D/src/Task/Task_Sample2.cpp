#include "Task_Sample2.h"
void Sample2::Initialize()
{
	std::cout << "Sample2‰Šú‰»" << std::endl;
	player.Initialize();
}

TaskFlag Sample2::UpDate()
{
	player.UpDate();
	TaskFlag nowtask = Task_Sample2;
	if (Input::KeyInputUp(Input::SPACE))
	{
		nowtask = Task_Sample;
	}
	return nowtask;
}

void Sample2::Render2D()
{
	player.Render();
}

void Sample2::Finalize()
{
	std::cout << "Sample2‰ð•ú" << std::endl;
	player.Finalize();
}