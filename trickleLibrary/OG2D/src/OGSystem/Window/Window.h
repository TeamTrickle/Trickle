#pragma once
#include "OGSystem\_OGsystem.h"

class Window {
private:
	GLFWimage image[1];
	GLuint id_;
public:
	int _widht;
	int _height;
	char* _Name;
	bool _Screen;
	GLFWwindow *window;
	typedef std::shared_ptr<Window> SP;
	static SP Create(int wi, int he, char* name, bool screen);
public:
	Window();
	Window(int wi, int he, char* name, bool screen);
	~Window();
	void createWindow(int wi, int he, char* name, bool screen);
	void setIcon(std::string& path_);
};