#include "Timer.h"
using namespace std;
Timer::Timer()
{

}
Timer::~Timer()
{

}
void Timer::Initialize()
{
	//時間のゼロクリア
	frame_time = 0;               //GetTimeの時間を代入する変数
	frame_time_sec = 0;           //秒
	frame_time_min = 0;           //分
	frame_time_hours = 0;         //時
}

void Timer::Update()
{
	
}
void Timer::Instrumentation()
{
	
}
void Timer::Instrumentation_output(Timer& timer_)
{
	cout << timer_.frame_time_hours << "時間" << timer_.frame_time_min << "分" << timer_.frame_time_sec << "秒" << endl;
}
void Timer::Frame_Set()
{
	frame_time = GetTime();
}
int Timer::Get_frame()
{
	return frame_time;
}