#include "Window.h"
#include "stb_image.h"
Window::Window()
{
	this->widht = 640;
	this->height = 480;
	this->screen = false;
	this->name = "NoName";
	this->isIcon = false;
	this->isVisualization = false;
}
Window::Window(const int wi, const int he, char* name, const bool screen, const Vec2& pos)
	:widht(wi)
	, height(he)
	, name(name)
	, screen(screen)
	, position(pos)
{
	if (screen) {
		window = glfwCreateWindow(widht, height, name, glfwGetPrimaryMonitor(), NULL);
	}
	else
	{
		window = glfwCreateWindow(widht, height, name, NULL, NULL);
	}
	if (!window) {
		glfwTerminate();
		return;
	}
	glfwSetWindowPos(this->window, (int)this->position.x, (int)this->position.y);
}
Window::~Window()
{
	glfwSetWindowIcon(this->window, 0, NULL);
}

bool Window::createWindow(const int wi, const int he, char* name, const bool screen, const Vec2& pos)
{
	this->widht = wi;
	this->height = he;
	this->name = name;
	this->screen = screen;
	this->position = pos;
	if (this->screen) {
		this->window = glfwCreateWindow(this->widht, this->height, this->name, glfwGetPrimaryMonitor(), NULL);
	}
	else
	{
		this->window = glfwCreateWindow(this->widht, this->height, this->name, NULL, NULL);
	}
	if (!this->window) {
		glfwTerminate();
		return false;
	}
	glfwSetWindowPos(this->window, (int)this->position.x, (int)this->position.y);
	return true;
}
void Window::setIcon(const std::string& path_)
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
	glfwSetWindowSizeLimits(this->window, this->widht, this->height, this->widht, this->height);
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
void Window::SetWindowPos(const Vec2& pos)
{
	this->position = pos;
}
GLFWwindow* Window::GetWindow() const
{
	return this->window;
}