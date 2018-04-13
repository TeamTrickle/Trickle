#include "OGsystem.h"
//--------------------------------------------------
//@:GameEngineclass									
//--------------------------------------------------
EngineSystem::EngineSystem()
{
	this->w_wi = 960;
	this->w_he = 540;
	this->w_na = "NoName";
	this->w_sc = false;
}
EngineSystem::EngineSystem(int widht, int height, char* name, bool screen)
{
	this->w_he = widht;
	this->w_he = height;
	this->w_na = name;
	this->w_sc = screen;
}
void EngineSystem::Initialize()
{
	gameEngine->camera = Camera2D::Create(Box2D(0, 0, 960, 540));
	gameEngine->window = Window::Create(w_wi, w_he, w_na, w_sc);
	gameEngine->fps = FPS::Create();
	gameEngine->window->setIcon(std::string("./data/image/testicon.png"));
	gameEngine->in.Inputinit(gameEngine->window->window);
	DebugFunction = false;
	this->isPause = false;
}
void EngineSystem::SetWindow(int width, int height, char* name, bool screen)
{
	this->w_wi = width;
	this->w_he = height;
	this->w_na = name;
	this->w_sc = screen;
}
void EngineSystem::Update()
{
	gameEngine->camera->CameraUpdate();
	gameEngine->in.upDate();
	gameEngine->fps->Update();
}
EngineSystem::~EngineSystem()
{
	gameEngine->fps->DeleteData();
}
void EngineSystem::SetPause(const bool ispause_)
{
	this->isPause = ispause_;
}
bool EngineSystem::GetPause() const
{
	return this->isPause;
}
EngineSystem* gameEngine;