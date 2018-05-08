#include "FPS.h"
FPS::FPS()
{
	this->fps = 0.f;
	//glfw内のTimeを初期化
	glfwSetTime(0.0);
	this->count = 0;
	//fps計測用
	this->lastTime = (float)glfwGetTime();
}
void FPS::Update() {
	//60回動作したらその時の時間と前の時間からfpsを求める
	if (this->count == 60) {
		this->fps = this->count / ((float)glfwGetTime() - this->lastTime);
#if(_DEBUG)
		std::cout << this->fps << std::endl;		//デバッグ時のみfpsを出力
#endif
		this->count = 0;
		this->lastTime = (float)glfwGetTime();
	}
	this->count++;
}
FPS::~FPS()
{

}
FPS::SP FPS::Create()
{
	//スマートポインタを返す
	return FPS::SP(new FPS());
}