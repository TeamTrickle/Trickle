#pragma once
//______________________________//
//|タイトルタスク               |//
//|履歴：2018/03/20金子翔       |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "Map\Map.h"

class Title:public TaskObject
{
	Texture texCursor;
	Texture texStart;
	Texture texClose;
	Texture texPause;

	Vec2 startPos;
	Vec2 pausePos;
	Vec2 closePos;
	Vec2 cursorPos;

	int nextTaskCheck;

public:
	Title();
	virtual ~Title();
	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();

	void CursorMove();
	//☆☆☆☆//
	//追加変数//
	//☆☆☆☆//
	Sound sound;

	enum State
	{
		Start,        //ゲームスタート
		Pause,         //設定
		Close        //ゲームを閉じる
	};
	State state;

	typedef std::shared_ptr<Title> SP;
	static SP Create(bool = true);
};