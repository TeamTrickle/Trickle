#include "Task_Sample2.h"
void Sample2::Initialize()
{
	std::cout << "Sample2‰Šú‰»" << std::endl;
	
}

TaskFlag Sample2::UpDate()
{
	TaskFlag nowtask = Task_Sample2;
	if (Key::KeyInputUp(GLFW_KEY_SPACE))
	{
		nowtask = Task_Sample;
	}
	return nowtask;
}

void Sample2::Render2D()
{

}

void Sample2::Finalize()
{
	std::cout << "Sample2‰ð•ú" << std::endl;
	
}