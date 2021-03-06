#pragma once
#include "_OGsystem.h"

class TaskObject
{
public:
	typedef std::shared_ptr<TaskObject> SP;	//スマートポインタ
	typedef std::weak_ptr<TaskObject> WP;	//サブオーバー
	WP me;									//自分の情報
private:
	bool NextTask;							//終了時に次のタスクを生成できるか
	int KillCount;							//削除するかどうかの判断用
	std::string taskName;					//タスクに名をつける
	float order;							//描画順番
	bool isPause;							//呼ばれる更新分岐
public:
	TaskObject();
	bool Init(const std::string&);				//初期化処理
	void T_UpDate();						//更新処理
	void T_Render();						//描画処理
	void T_Pause();							//停止処理
	virtual void UpDate();					//子達の更新処理
	virtual void Render2D();				//子達の描画処理
	virtual void PauseUpDate();				//子達の停止処理
	void Kill(bool = true);					//削除処理
	int GetKillCount();						//削除状況を返す
	bool GetNextTask();						//次のタスクが作れるかどうかを返す
	void ResetKillCount();					//削除状況をリセットする
	void SetDrawOrder(float);				//描画順を登録する
	float GetDrawOrder() const;				//描画順を返す
	std::string GetTaskName() const;		//タスク名を返す
	bool GetPause() const;
	void SetPause(const bool);
	void Stop(const bool = true);
	bool GetIsStop() const;
private:
};