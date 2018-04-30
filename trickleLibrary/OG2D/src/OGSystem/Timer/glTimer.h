#pragma once

#include "OGSystem\_OGsystem.h"

class Time
{
public:
	Time();
	~Time();
	//計測開始
	void Start();
	//計測停止
	void Stop();
	//一時停止
	void Pause();
	//現在タイム
	float GetTime();
	//開始タイムの変更
	void InitTime(const float time_);
	//計測判定
	bool isplay() const;
private:
	//初期タイム
	float initTime;
	//現在タイム
	float nowTime;
	//停止中のタイムの保存
	float saveTime;
	//追加タイム
	float addTime;
	//計測中判定
	bool isPlay;
	//動作中判定
	bool behavior;
};