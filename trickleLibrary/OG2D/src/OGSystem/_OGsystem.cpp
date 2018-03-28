#include "_OGsystem.h"

void Vec2::Normalize() {
	float len = this->GetLength();
	if (len == 0) { return; }
	x /= len;
	y /= len;
}
float Vec2::GetLength() {
	return powf(x*x + y*y, 0.5f);
}



void FPS::Initialize() {
	fps = 0.f;
	glfwSetTime(0.0);
	count = 0;
	lastTime = (float)glfwGetTime();
}
void FPS::Update() {
	if (count == 60) {
		fps = count / ((float)glfwGetTime() - lastTime);
		std::cout << fps << std::endl;
		count = 0;
		lastTime = (float)glfwGetTime();
	}
	count++;
}
Window::Window()
{
	this->_widht = 640;
	this->_height = 480;
	this->_Screen = false;
	this->_Name = "NoName";
}
Window::Window(int wi, int he, char* name, bool screen) 
	:_widht(wi)
	, _height(he)
	, _Name(name)
	, _Screen(screen)
	{
	if (_Screen) {
		window = glfwCreateWindow(_widht, _height, _Name, glfwGetPrimaryMonitor(), NULL);
	}
	else
	{
		window = glfwCreateWindow(_widht, _height, _Name, NULL, NULL);
	}
	if (!window) {
		glfwTerminate();
		return;
	}
}
Window::~Window()
{

}

Window::SP Window::Create(int wi, int he, char* name, bool screen)
{
	return Window::SP(new Window(wi, he, name, screen));
}

void Window::createWindow(int wi, int he, char* name, bool screen)
{
	this->_widht = wi;
	this->_height = he;
	this->_Name = name;
	this->_Screen = screen;
	if (this->_Screen) {
		this->window = glfwCreateWindow(this->_widht, this->_height, this->_Name, glfwGetPrimaryMonitor(), NULL);
	}
	else
	{
		this->window = glfwCreateWindow(this->_widht, this->_height, this->_Name, NULL, NULL);
	}
	if (!this->window) {
		glfwTerminate();
		return;
	}
}