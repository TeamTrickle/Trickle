#pragma once
#include "OGSystem\_OGsystem.h"

class FPS {
public:
	FPS();							//コンストラクタ
	~FPS();							//デストラクタ
	void Update();					//更新処理
	/**
	*@brief	:フレームチェック
	*@return:秒間フレームに達しているならtrue
	*/
	bool FrameCheck();
private:
	float lastTime;					//前フレームタイム
	int count;						//カウント数
	GLfloat fps;					//fps値
	//! frame rate
	int framerate;
	//! oneframetime
	float oneFrameTime;
};
