#pragma once
//_____________________________
//|タスクシステム               
//|履歴：2018/03/20    
//|____________________________
#include "OGSystem\OGsystem.h"
#include "Task\Task_Sample.h"

class OGTK
{
public:
	void _myGameInitialize();		//GammeEngineの初期化時に設定したい処理を行う初期化関数
	void StartTaskObject();			//開始時に生成したいタスクを指定する関数
};