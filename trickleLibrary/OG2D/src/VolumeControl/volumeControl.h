#pragma once
#include "OGSystem\OGsystem.h"


class VolumeControl :public Sound
{
	Vec2* playerPos;        //自身(プレイヤーの位置)
	Vec2 soundPos;          //音源の位置
	float distance;         //音源とプレイヤの直線距離
	float maxdis;
	float maxvol;
	//フェードイン関連に使用する
	int timer;
	float fadeinBGM;
	float fadeoutBGM;
public:
	VolumeControl();
	~VolumeControl();
	float GetDistance(Vec2* soundpos);      //音源とプレイヤとの距離を求める
	float VolSet();                        //音量を距離によって変更させる
	void GetPlPos();                       //プレイヤの位置を求める
	void Play(Vec2* pos, float maxDis, float maxVol, Sound&sound);
	float FadeIn(bool canControl);         //BGMのフェードイン
	float FadeOut(bool canControl);        //BGMのフェードアウト
};