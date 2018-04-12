#include "FPS.h"
FPS::FPS()
{
	fps = 0.f;
	glfwSetTime(0.0);
	count = 0;
	lastTime = (float)glfwGetTime();
	this->Setfps = 60.f;
	this->setlast = (float)glfwGetTime();
}
void FPS::Initialize() {
	fps = 0.f;
	glfwSetTime(0.0);
	count = 0;
	lastTime = (float)glfwGetTime();
	this->Setfps = 60.f;
	this->setlast = (float)glfwGetTime();
}
void FPS::Update() {
	if (count == 60) {
		fps = count / ((float)glfwGetTime() - lastTime);
		std::cout << fps << std::endl;
		count = 0;
		lastTime = (float)glfwGetTime();
	}
	count++;
	float current = glfwGetTime();
	float elapsed = current - this->setlast;
	if (elapsed >= 1.0)
	{
		for (int i = 0; i < data.size(); ++i)
		{
			this->data[i]();
		}
		this->setlast = glfwGetTime();
	}
}
	
void FPS::SetData(void data_())
{
	this->data.push_back(data_);
}
void FPS::DeleteData()
{
	this->data.clear();
}
FPS::~FPS()
{
	data.clear();
}
FPS::SP FPS::Create()
{
	return FPS::SP(new FPS());
}