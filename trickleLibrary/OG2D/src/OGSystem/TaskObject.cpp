#include "TaskObject.h"
TaskObject::TaskObject()
{
	this->taskName = "";
	this->KillCount = 0;
	this->NextTask = true;
	this->order = 0.0f;
	this->isPause = false;
}
bool TaskObject::Init(const std::string& name_)
{
	this->taskName = name_;
	return true;
}
void TaskObject::T_UpDate()
{
	if (!this->isPause)
	{
		UpDate();
	}
	else
	{
		PauseUpDate();
	}
}
void TaskObject::T_Render()
{
	Render2D();
}
void TaskObject::Kill(bool on)
{
	this->NextTask = on;
	if (this->KillCount < 0)
	{
		this->KillCount++;
	}
	this->KillCount++;
}
int TaskObject::GetKillCount()
{
	return this->KillCount;
}
bool TaskObject::GetNextTask()
{
	return this->NextTask;
}
void TaskObject::ResetKillCount()
{
	this->KillCount = 0;
}
void TaskObject::SetDrawOrder(float order_)
{
	if (order_ >= 0.0f)
	{
		this->order = order_;
	}
	else
	{
		this->order = 0.0f;
	}
}
float TaskObject::GetDrawOrder() const
{
	return this->order;
}
std::string TaskObject::GetTaskName() const
{
	return this->taskName;
}
void TaskObject::T_Pause()
{
	PauseUpDate();
}
void TaskObject::UpDate()
{

}
void TaskObject::Render2D()
{

}
void TaskObject::PauseUpDate()
{

}
void TaskObject::SetPause(const bool flag)
{
	this->isPause = flag;
}
bool TaskObject::GetPause() const
{
	return this->isPause;
}

void TaskObject::Stop(const bool flag)
{
	if (this->KillCount > 0)
	{
		return;
	}
	if (flag)
	{
		this->KillCount = -1;
	}
	else
	{
		this->KillCount = 0;
	}
}
bool TaskObject::GetIsStop() const
{
	return this->KillCount == 0 ? true : false;
}