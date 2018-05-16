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
void TaskObject::Draw2D()
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
	this->order = order_;
}
float TaskObject::GetDrawOrder() const
{
	return this->order;
}
std::string TaskObject::GetTaskName() const
{
	return this->taskName;
}