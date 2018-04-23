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
	this->Cursor_on = true;
	this->file = "testicon.png";
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
	gameEngine->window->LimitsWindow();
	gameEngine->window->InMouseMode(this->Cursor_on);
	gameEngine->fps = FPS::Create();
	gameEngine->window->setIcon(this->path + this->file);
	gameEngine->in.Inputinit(gameEngine->window->window);
	gameEngine->soundManager = SoundManager::Create();
	gameEngine->audiodevice = Audio::Create();
	DebugFunction = false;
	this->isPause = false;
	this->end = false;
}
void EngineSystem::SetWindow(int width, int height, char* name, bool screen)
{
	this->w_wi = width;
	this->w_he = height;
	this->w_na = name;
	this->w_sc = screen;
}
void EngineSystem::SetCursorOn(const bool on)
{
	this->Cursor_on = on;
}
void EngineSystem::SetIcon(std::string filepath_)
{
	this->file = filepath_;
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
void EngineSystem::GameEnd()
{
	this->end = true;
}
bool EngineSystem::GetEnd() const
{
	return this->end;
}
void EngineSystem::ChengeTask()
{
	gameEngine->camera->SetPos(Vec2(0.f, 0.f));
	gameEngine->camera->SetSize(Vec2(gameEngine->window->_widht, gameEngine->window->_height));
	gameEngine->fps->DeleteData();
	gameEngine->SetPause(false);
	gameEngine->soundManager->AllDelete();
}
EngineSystem* gameEngine;