#include "Task_Result.h"
using namespace std;
Result::Result()
{
	cout << "結果画面処理初期化" << endl;
}
Result::~Result()
{
	cout << "結果画面処理解放" << endl;
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