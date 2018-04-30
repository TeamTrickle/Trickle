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
	//ŠÔ‚Ìƒ[ƒƒNƒŠƒA
	frame_time = 0;               //GetTime‚ÌŠÔ‚ğ‘ã“ü‚·‚é•Ï”
}
void Timer::Frame_Set()
{
	frame_time = GetTime();
}
int Timer::Get_frame()
{
	return frame_time;
}