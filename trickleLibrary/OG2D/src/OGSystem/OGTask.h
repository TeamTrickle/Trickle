#pragma once
//______________________________//
//|タスクシステム               |//
//|履歴：2018/03/20金子翔       |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "Win\WinMain.h"
//☆☆☆☆☆☆☆☆☆//
//追加タスク       //
//☆☆☆☆☆☆☆☆☆//
#include "Task\Task_Game.h"
#include "Task\Task_Title.h"
#include "Task\Task_Option.h"
#include "Task\Task_Result.h"
#include "Task\StageSelect.h"

class _OGTK
{
public:
	//☆☆☆☆☆☆☆☆☆//
	//タスクclassの宣言//
	//☆☆☆☆☆☆☆☆☆//
	//タスクclassの追加はここに
	//cppにも同様に記述
	Game game;
	Title title;
	Option option;
	Result result;
	StageSelect select;

	////////////////////////////
	//ここから下は変更しないこと//
	///////////////////////////
	//タスク変数
	TaskFlag nowTask, nextTask;
	//生成ウィンドウ
	//Window _window;
	//タスクシステム関数
	void _myGameInitialize();
	void _myGameUpdate();
	void _myGameRender2D();
	void _myGameRender3D();
	void _myGameFinalize();
};