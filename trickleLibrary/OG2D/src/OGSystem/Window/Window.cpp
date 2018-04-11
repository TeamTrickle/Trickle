#include "Window.h"
#include "stb_image.h"
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
	glfwSetWindowIcon(this->window, 0, NULL);
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
void Window::setIcon(std::string& path_)
{
	image[0].pixels = stbi_load(path_.c_str(), &image[0].width, &image[0].height, 0, 4);
	glfwSetWindowIcon(this->window, 1, image);
	stbi_image_free(image[0].pixels);
}