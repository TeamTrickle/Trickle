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
	frame_time = 0;               //1フレームごとに格納するタイム
	frame_time_sec = 0;           //秒
	frame_time_min = 0;           //分
	frame_time_hours = 0;         //時

}
void Timer::Update()
{
	Instrumentation();            //タイマーの計算をする
	Instrumentation_output();     //タイマーの出力をする
}
void Timer::Instrumentation()
{
	frame_time++;                 //タイマーを動かす
	//計算式
	if (frame_time == 60)         //タイマーが60フレームいったら・・・
	{
		frame_time_sec += frame_time / 60;                         //秒の計算
		frame_time = 0;                                            //ゼロクリア
		if (frame_time_sec == 60) //60秒になったら・・・
		{
			frame_time_min += frame_time_sec / 60;                 //分の計算
			frame_time_sec = 0;                                    //ゼロクリア
		}
		if (frame_time_min == 60) //60分になったら・・・
		{
			frame_time_hours += frame_time_min / 60;               //時間の計算
			frame_time_min = 0;                                    //ゼロクリア
		}
	}
}
void Timer::Instrumentation_output()
{
	if (frame_time % 60 == 0) //60フレームにつき一回だけ出力します
	{
		cout << frame_time_hours << "時間" << frame_time_min << "分" << frame_time_sec << "秒" << endl;
	}
}
void Timer::Instrumentation_output(Timer& timer_)
{
	cout << timer_.frame_time_hours << "時間" << timer_.frame_time_min << "分" << timer_.frame_time_sec << "秒" << endl;
}