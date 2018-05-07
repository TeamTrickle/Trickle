#pragma once
//_____________________________
//|システムクラス２             
//|履歴：2018/03/20       
//|履歴：2018/03/23		   
//|____________________________
#include "Camera\Camera.h"
#include "Window\Window.h"
#include "FPS\FPS.h"
#include "Input\Input.h"
#include "Font\Font.h"
#include "Texture\Texture.h"
#include "Collision\Collision.h"
#include "Font\Font.h"
#include "Audio\SoundManager.h"
#include "Timer\glTimer.h"
#include "Easing\easing.hpp"
#include "Audio\StreamingSound.h"
#include "Random\Random.h"

class EngineSystem
{
public:
	EngineSystem();			//コンストラクタ
	EngineSystem(			//コンストラクタ
		int,
		int,
		char*,
		bool = false);
	~EngineSystem();		//デストラクタ
	Camera2D::SP camera;	//カメラ2D
	Window::SP window;		//Window
	FPS::SP fps;			//fps
	Audio::SP audiodevice;	//Audio
	SoundManager::SP soundManager;	//Sound管理
	Input in;				//入力状況
	void Initialize();		//初期化処理
	void Update();			//更新処理
	void SetWindow(			//Window情報登録
		int,
		int,
		char*,
		bool = false);
	void SetWindowPos(Vec2&);	//Window生成位置設定
	void SetCursorOn(const bool);	//カーソル可視化有無
	void SetIcon(std::string&);	//アイコン使用画像設定
	bool DebugFunction;		//デバッグ機能
	void SetPause(const bool);	//ポーズ設定
	bool GetPause() const;		//ポーズを返す
	void GameEnd();				//アプリケーション終了登録
	bool GetEnd() const;		//アプリケーション終了を返す
	void ChengeTask();			//タスク変更時処理
	bool GetDeleteEngine();		//エンジン終了を返す
	void SetDeleteEngine(bool);	//エンジン終了登録
private:
	bool end;			//終了状況
	int w_wi;			//WindowSize
	int w_he;			//WindowSize
	char* w_na;			//WindowName
	bool w_sc;			//WindowMode
	bool isPause;		//PauseCheck
	bool Cursor_on;		//カーソル可視化
	std::string path = "./data/image/";	//ファイルパス
	std::string file;	//ファイル名
	Vec2 w_pos;			//WindowPosition
	bool DeleteEngine;	//Engine終了状況
};

extern EngineSystem* gameEngine;