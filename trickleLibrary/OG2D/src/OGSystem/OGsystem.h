#pragma once
//______________________________//
//|システムクラス２              |//
//|履歴：2018/03/20金子翔       |//
//|履歴：2018/03/23金子翔		   |//
//|____________________________|//
#include "Camera\Camera.h"
#include "Window\Window.h"
#include "Audio\Audio.h"
#include "FPS\FPS.h"
#include "Input\Input.h"
#include "Font\Font.h"
#include "Texture\Texture.h"
#include "Collision\Collision.h"
#include "Audio\Sound.h"
#include "Font\Font.h"
/*
#include "Audio\StreamingSound.h"
*/
class EngineSystem
{
public:
	EngineSystem();
	EngineSystem(int widht, int height, char* name, bool screen);
	~EngineSystem();
	Camera2D::SP camera;
	Window::SP window;
	FPS::SP fps;
	Input in;
	void Initialize();
	void Update();
	void SetWindow(int width, int height, char* name, bool screen);
	bool DebugFunction;
	void SetPause(const bool ispause_);
	bool GetPause() const;
private:
	int w_wi;
	int w_he;
	char* w_na;
	bool w_sc;
	bool isPause;
};

extern EngineSystem* gameEngine;