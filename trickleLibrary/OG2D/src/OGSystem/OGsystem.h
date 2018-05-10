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
#include "Texture\Texture.h"
#include "Collision\Collision.h"
#include "Font\Font.h"
#include "Audio\SoundManager.h"
#include "Timer\glTimer.h"
#include "Easing\easing.hpp"
#include "Audio\StreamingSound.h"
#include "Random\Random.h"
#include "TaskObject.h"

class OrderCheck
{
public:
	OrderCheck()
	{
		this->id = -1;
		this->order_s = -1.f;
	}
	int id;
	float order_s;
};

class EngineSystem
{
private:
	bool end;			//終了状況
	int w_wi;			//WindowSize
	int w_he;			//WindowSize
	char* w_na;			//WindowName
	bool w_sc;			//WindowMode
	bool isPause;		//PauseCheck
	bool Cursor_on;		//カーソル可視化
	const std::string path = "./data/image/";	//ファイルパス
	std::string file;	//ファイル名
	Vec2 w_pos;			//WindowPosition
	std::vector<OrderCheck> Orders;	//描画順
	bool DeleteEngine;	//Engine終了状況
public:
	EngineSystem();			//コンストラクタ
	EngineSystem(			//コンストラクタ
		int,
		int,
		char*,
		bool = false);
	~EngineSystem();		//デストラクタ
	//Camera2D::SP camera;	//カメラ2D
	Camera2D* camera;
	//Window::SP window;		//Window
	Window* window;
	//FPS::SP fps;			//fps
	FPS* fps;
	//Audio::SP audiodevice;//Audio
	Audio* audiodevice;
	//SoundManager::SP soundManager;//Sound管理
	SoundManager* soundManager;
	//Input in;				//入力状況
	Input* in;
	
	bool Initialize();		//初期化処理
	void Update();			//更新処理
	void SetWindow(			//Window情報登録
		int,
		int,
		char*,
		bool = false);
	void SetWindowPos(Vec2&);	//Window生成位置設定
	void SetCursorOn(const bool);	//カーソル可視化有無
	void SetIcon(std::string&);	//アイコン使用画像設定
	bool DebugFunction;			//デバッグ機能
	void SetPause(const bool);	//ポーズ設定
	bool GetPause() const;		//ポーズを返す
	void GameEnd();				//アプリケーション終了登録
	bool GetEnd() const;		//アプリケーション終了を返す
	void ChengeTask();			//タスク変更時処理
	void TaskGameUpDate();		//タスク達の更新処理
	void SetTaskObject(			//タスクを登録
		const TaskObject::SP&);
	bool GetDeleteEngine();		//エンジン終了を返す
	void SetDeleteEngine(bool);	//エンジン終了登録
	//template <class T>std::shared_ptr<T> GetTask(const std::string&);
	//タスク検索(最初の同名のタスクを返す)
	template <class T> std::shared_ptr<T> GetTask(const std::string& taskName)
	{
		for (auto id = this->taskobjects.begin(); id != this->taskobjects.end(); ++id)
		{
			if ((*id).second->GetTaskName() == taskName)
			{
				return std::static_pointer_cast<T>((*id).second);
			}
		}
		return nullptr;
	}
private:
	void TaskApplication();	//タスク登録予定を登録する
	void ConfigDrawOrder();	//描画順を設定する
	bool CheckAddTask();	//登録予定のタスクの有無
	bool CheckKillTask();	//削除予定のタスクの有無
	void Task_UpDate();			//タスク更新処理
	void Task_Render_AF();		//タスク描画処理
	void TaskKillCheck();		//削除予定のタスクを削除
	void AllTaskDelete();		//登録タスク全削除
	std::vector<std::pair<DWORD, TaskObject::SP>> taskobjects;	//タスクオブジェクト達
	std::vector<TaskObject::SP> addTaskObjects;	//登録予定タスク達
};

extern EngineSystem* OGge;