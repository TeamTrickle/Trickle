#include "glTimer.h"

Time::Time()
{
	this->initTime = 0.0f;
	this->nowTime = 0.0f;
	this->saveTime = 0.0f;
	this->addTime = 0.0f;
	this->isPlay = false;
	this->behavior = false;
}

Time::~Time()
{

}

void Time::Start()
{
	if (!this->isPlay && !this->behavior) {
		this->initTime = (float)glfwGetTime() + this->addTime;
		this->isPlay = true;
		this->behavior = true;
	}
}

void Time::Stop()
{
	if (this->isPlay && this->behavior) {
		this->initTime = 0.0f;
		this->nowTime = 0.0f;
		this->saveTime = 0.0f;
		this->addTime = 0.0f;
		this->isPlay = false;
		this->behavior = false;
	}
}

void Time::Pause()
{
	if (this->behavior) {
		if (this->isPlay)
		{
			//ˆêŽž’âŽ~
			float a = (float)glfwGetTime();
			this->nowTime = (float)glfwGetTime() - this->initTime;
			this->saveTime = this->nowTime;
			this->isPlay = false;
		}
		else
		{
			//Œ³‚ÌˆÊ’u‚©‚çÄ‚ÑŠJŽn
			this->initTime = (float)glfwGetTime() - this->saveTime;
			this->saveTime = 0.0f;
			this->isPlay = true;
		}
	}
}

float Time::GetTime()
{
	if (!this->behavior) { return 0.0f; }
	if (this->isPlay) {
		this->nowTime = (float)glfwGetTime() - this->initTime;
	}
	return this->nowTime;
}

void Time::InitTime(const float time_)
{
	this->addTime = time_;
}

bool Time::isplay() const
{
	return this->isPlay;
}