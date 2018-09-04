/**
*フレームレートを計算,制限するclass
*既存GameEngineを使用している場合はDEBUG時のみ自動で生成される
*/
#pragma once
#include "OGSystem\_OGsystem.h"

class FPS {
public:
	/**
	*@brief	:constructor
	*/
	FPS();
	/**
	*@brief	:destructor
	*/
	~FPS();
	/**
	*@brief	:更新処理
	*/
	void Update();
	/**
	*@bried	:フレームレート指定*
	*@param	:int rate frame rate
	*/
	void SetFrameRate(const int rate);
	/**
	*@brief	:フレームチェック
	*@return:秒間フレームに達しているならtrue
	*/
	bool FrameCheck();
private:
	//! 全フレームタイム
	float lastTime;
	//! カウント数
	int count;
	//! fps値
	GLfloat fps;
	//! frame rate
	int framerate;
	//! oneframetime
	float oneFrameTime;
};
