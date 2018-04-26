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
	this->camera = Camera2D::Create(Box2D(0, 0, 960, 540));
	this->window = Window::Create(w_wi, w_he, w_na, w_sc);
	this->window->LimitsWindow();
	this->window->InMouseMode(this->Cursor_on);
	this->fps = FPS::Create();
	this->window->setIcon(this->path + this->file);
	this->in.Inputinit(this->window->window);
	this->soundManager = SoundManager::Create();
	this->audiodevice = Audio::Create();
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
	this->camera->CameraUpdate();
	this->in.upDate();
	this->fps->Update();
}
EngineSystem::~EngineSystem()
{
	this->fps->DeleteData();
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
	this->camera->SetPos(Vec2(0.f, 0.f));
	this->camera->SetSize(Vec2(this->window->_widht, this->window->_height));
	this->fps->DeleteData();
	this->SetPause(false);
	this->soundManager->AllDelete();
}
EngineSystem* gameEngine;