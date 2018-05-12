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
bool EngineSystem::Initialize()
{
	//初期化処理
	//Windowの生成
	this->window = new Window(w_wi, w_he, w_na, w_sc, w_pos);
	//Window設定
	this->window->LimitsWindow();
	this->window->InMouseMode(this->Cursor_on);
	this->window->setIcon(this->path + this->file);
	//カメラ2Dの生成
	this->camera = new Camera2D(Box2D(0, 0, w_wi, w_he));
	//fpsの設定
	//※デバッグ時のみ使用する
#if(_DEBUG)
	this->fps = new FPS();
#endif
	//入力関連の初期化
	this->in = new Input();
	this->in->Inputinit(this->window->GetWindow());
	//サウンド管理の初期化
	this->soundManager = new SoundManager();
	//オーディオデバイスの初期化と設定
	this->audiodevice = new Audio();
	//各値の初期化
	DebugFunction = false;
	this->isPause = false;
	this->end = false;
	return true;
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
	this->in->upDate();
#if(_DEBUG)
	this->fps->Update();
#endif
}
void EngineSystem::Task_UpDate()
{
	//登録タスクの更新処理を呼ぶ
	for (int id = 0; id < this->taskobjects.size();++id)
	{
		if (this->taskobjects[id].second->GetKillCount() == 0) 
		{
			this->taskobjects[id].second->T_UpDate();
		}
	}
}
void EngineSystem::Task_Render_AF()
{
	//描画順にDraw2Dを実行する
	for (int i = 0; i < this->taskobjects.size(); ++i)
	{
		if (this->taskobjects[this->Orders[i].id].second->GetKillCount() == 0)
		{
			this->taskobjects[this->Orders[i].id].second->Draw2D();
		}
	}
}
void EngineSystem::TaskGameUpDate()
{
	this->Task_UpDate();		//更新処理
	this->Task_Render_AF();		//描画処理
	if (this->CheckAddTask() || this->CheckKillTask())
	{
		this->TaskApplication();	//登録予定のタスクを登録する
		this->TaskKillCheck();		//削除予定のタスクを削除する
		this->ConfigDrawOrder();	//タスクの集合体の変更後に描画順を設定する
	}
}
void EngineSystem::ConfigDrawOrder()
{
	//描画順の設定
	//登録タスク分の描画順を入れておくclassを作っておく
	this->Orders.resize(this->taskobjects.size());
	//初期状態をコピーする
	for (int i = 0; i < this->taskobjects.size(); ++i)
	{
		this->Orders[i].id = i;
		this->Orders[i].order_s = this->taskobjects[i].second->GetDrawOrder();
	}
	//描画順に合わせてidとorderを並び替える
	for (int i = 0; i < this->taskobjects.size(); ++i)
	{
		for (int j = i; j < this->taskobjects.size(); ++j)
		{
			if (this->Orders[i].order_s > this->Orders[j].order_s)
			{
				OrderCheck kari = this->Orders[i];
				this->Orders[i] = this->Orders[j];
				this->Orders[j] = kari;
			}
		}
	}
}
EngineSystem::~EngineSystem()
{
	//登録しているタスクをすべて破棄する
	this->AllTaskDelete();
	//生成したclassをdeleteする
	delete this->audiodevice;
	delete this->soundManager;
#if(_DEBUG)
	delete this->fps;
#endif
	delete this->in;
	delete this->window;
	delete this->camera;
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
	this->camera->SetSize(this->window->GetSize());
	this->SetPause(false);
	//this->soundManager->AllDelete();
}
void EngineSystem::SetTaskObject(const TaskObject::SP& To)
{
	//タスクを登録予定に登録
	this->addTaskObjects.push_back(To);
}
void EngineSystem::TaskApplication()
{
	//登録予定のものを登録する
	for (int i = 0; i < this->addTaskObjects.size(); ++i)
	{
		std::pair<DWORD, TaskObject::SP> d;
		d.second = this->addTaskObjects[i];
		if (d.second->GetNextTask())
		{
			this->taskobjects.push_back(d);
		}
	}
	addTaskObjects.clear();
}
void EngineSystem::TaskKillCheck()
{
	//削除予定のタスクを削除する
	auto id = this->taskobjects.begin();
	while (id != this->taskobjects.end())
	{
		if (id->second->GetKillCount() > 0)
		{
			this->taskobjects.erase(id);
			this->TaskApplication();
			id = this->taskobjects.begin();
		}
		else
		{
			++id;
		}
	}
}
bool EngineSystem::CheckAddTask()
{
	return this->addTaskObjects.size() > 0;
}
bool EngineSystem::CheckKillTask()
{
	for (int i = 0; i < this->taskobjects.size(); ++i)
	{
		if (taskobjects[i].second->GetKillCount() > 0)
		{
			return true;
		}
	}
	return false;
}
void EngineSystem::AllTaskDelete()
{
	//全削除
	this->taskobjects.clear();
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
//template <class T> std::shared_ptr<T> EngineSystem::GetTask(const std::string& taskName)
//{
//	for (auto id = this->taskobjects.begin(); id != this->taskobjects.end(); ++id)
//	{
//		if ((*id).second->taskName == taskName)
//		{
//			return std::static_pointer_cast<T>((*id).second);
//		}
//	}
//	return nullptr;
//}
EngineSystem* OGge;
ResourceManager* rm;