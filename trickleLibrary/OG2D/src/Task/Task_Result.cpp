#include "Task_Result.h"
using namespace std;
Result::Result()
{
	cout << "Œ‹‰Ê‰æ–Êˆ—‰Šú‰»" << endl;
}
Result::~Result()
{
	cout << "Œ‹‰Ê‰æ–Êˆ—‰ð•ú" << endl;
}
void Result::Initialize()
{

}
TaskFlag Result::Update()
{
	TaskFlag nowTask = TaskFlag::Task_Ruselt;
	if (gameEngine->in.key.down(Input::KeyBoard::S))
	{
		nowTask = Task_Title;
	}
	return nowTask;
}
void Result::Render()
{
	
}
void Result::Finalize()
{
	image.Finalize();
}