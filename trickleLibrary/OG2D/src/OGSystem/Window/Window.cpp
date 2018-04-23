#include "Window.h"
#include "stb_image.h"
Window::Window()
{
	this->_widht = 640;
	this->_height = 480;
	this->_Screen = false;
	this->_Name = "NoName";
	this->isIcon = false;
	this->isVisualization = false;
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
	//stbimageを使って画像を読み込む
	image[0].pixels = stbi_load(path_.c_str(), &image[0].width, &image[0].height, 0, 4);
	//glfwに設定したいWindowとアイコンにしたい画像データと個数を送る
	glfwSetWindowIcon(this->window, 1, image);
	//データの解放
	stbi_image_free(image[0].pixels);
}
void Window::LimitsWindow()
{
	//Windowのサイズを固定化させる
	glfwSetWindowSizeLimits(this->window, this->_widht, this->_height, this->_widht, this->_height);
	//windowのアスペクト比を固定させる
	glfwSetWindowAspectRatio(this->window, 16, 9);
	//windowのサイズを変更する(固定化されている場合変更はできない)
	//glfwSetWindowSize(this->window, 1920, 1080);
}
void Window::WindowIcon()
{
	if (this->isIcon)
	{
		//Icon化されたwindowを元に戻す
		glfwRestoreWindow(this->window);
		this->isIcon = false;
	}
	else
	{
		//windowをIcon化させる
		glfwIconifyWindow(this->window);
		this->isIcon = true;
	}
}

void Window::Visualization()
{
	if (this->isVisualization)
	{
		//隠れたwindowを元に戻す
		glfwShowWindow(this->window);
		this->isVisualization = false;
	}
	else
	{
		//windowを隠す
		glfwHideWindow(this->window);
		this->isVisualization = true;
	}
}

void Window::InMouseMode(const bool index)
{
	if (index)
	{
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else
	{
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
}
Vec2 Window::GetSize() const
{
	int w, h;
	glfwGetWindowSize(this->window, &w, &h);
	return Vec2(w, h);
}
Vec2 Window::GetPos() const
{
	int x, y;
	glfwGetWindowPos(this->window, &x, &y);
	return Vec2(x, y);
}