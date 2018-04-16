#pragma once
//______________________________//
//|サンプルタスク               |//
//|履歴：2018/03/20金子翔       |//
//|____________________________|//
#include "Win\WinMain.h"
#include "OGSystem\OGsystem.h"

class Sample
{
public:
	void Initialize();
	TaskFlag UpDate();
	void Render2D();
	void Finalize();
	//☆☆☆☆//
	//追加変数//
	//☆☆☆☆//
	Sound s;
	Sound a;
	std::string file2 = "stereo.wav";
	std::string file = "playandhope.wav";
};