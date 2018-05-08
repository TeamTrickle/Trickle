#include "OGsystem.h"
//--------------------------------------------------
//@:GameEngineclass									
//--------------------------------------------------
EngineSystem::EngineSystem()
{
	//Window情報がセットされなかった時のための初期設定
	this->w_wi = 960;
	this->w_he = 540;
	this->w_na = "NoName";
	this->w_sc = false;
	this->Cursor_on = true;
	this->file = "testicon.png";
	this->w_pos = { 1920 - this->w_wi, 50 };
	this->DeleteEngine = false;
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
	//初期化処理
	//カメラ2Dの生成
	this->camera = Camera2D::Create(Box2D(0, 0, 960, 540));
	//Windowの生成
	this->window = Window::Create(w_wi, w_he, w_na, w_sc, w_pos);
	//Window設定
	this->window->LimitsWindow();
	this->window->InMouseMode(this->Cursor_on);
	this->window->setIcon(this->path + this->file);
	//fpsの設定
	//※デバッグ時のみ使用する
#if(_DEBUG)
	this->fps = FPS::Create();
#endif
	//入力関連の初期化
	this->in.Inputinit(this->window->window);
	//サウンド管理の初期化
	this->soundManager = SoundManager::Create();
	//オーディオデバイスの初期化と設定
	this->audiodevice = Audio::Create();
	//各値の初期化
	DebugFunction = false;
	this->isPause = false;
	this->end = false;
}
void EngineSystem::SetWindow(int width, int height, char* name, bool screen)
{
	//Window情報を登録する
	this->w_wi = width;
	this->w_he = height;
	this->w_na = name;
	this->w_sc = screen;
}
void EngineSystem::SetCursorOn(const bool on)
{
	//カーソルの可視化有無
	this->Cursor_on = on;
}
void EngineSystem::SetIcon(std::string& filepath_)
{
	//アイコンに使用する画像の設定
	this->file = filepath_;
}
void EngineSystem::Update()
{
	//カメラと入力状況の更新
	this->camera->CameraUpdate();
	this->in.upDate();
#if(_DEBUG)
	this->fps->Update();
#endif
}
void EngineSystem::SetPause(const bool ispause_)
{
	//ポーズ設定
	this->isPause = ispause_;
}
bool EngineSystem::GetPause() const
{
	//ポーズ状況を返す
	return this->isPause;
}
void EngineSystem::GameEnd()
{
	//アプリケーションの終了予定設定
	this->end = true;
}
bool EngineSystem::GetEnd() const
{
	//アプリケーションを終了の有無を返す
	return this->end;
}
void EngineSystem::ChengeTask()
{
	//タスクを変更する際に元に戻したい処理
	this->camera->SetPos(Vec2(0.f, 0.f));
	this->camera->SetSize(Vec2(this->window->_widht, this->window->_height));
	this->SetPause(false);
	this->soundManager->AllDelete();
}
void EngineSystem::SetWindowPos(Vec2& pos)
{
	//Windowの位置を返す
	this->w_pos = pos;
}
void EngineSystem::SetDeleteEngine(bool flag)
{
	//エンジンの終了を登録
	this->DeleteEngine = flag;
}
bool EngineSystem::GetDeleteEngine()
{
	//エンジン終了を返す
	return this->DeleteEngine;
}
EngineSystem::~EngineSystem()
{

}
EngineSystem* gameEngine;