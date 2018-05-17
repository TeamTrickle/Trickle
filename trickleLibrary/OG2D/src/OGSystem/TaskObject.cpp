#include "TaskObject.h"

bool TaskObject::Init(std::string& name_)
{
	this->taskName = name_;
	this->KillCount = 0;
	this->NextTask = true;
	this->order = 0.0f;
	return true;
}
void TaskObject::T_UpDate()
{
	UpDate();
}
void TaskObject::T_Render()
{
	Render2D();
}
void TaskObject::Kill(bool on)
{
	this->NextTask = on;
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
	Pause();
}
void TaskObject::UpDate()
{

}
void TaskObject::Render2D()
{

}
void TaskObject::Pause()
{

}
