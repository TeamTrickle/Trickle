#pragma once
#include "OGSystem\OGSystem.h"

class LogoTask : public TaskObject
{
	/**
	*enum Mode
	*状態管理
	*/
	enum Mode
	{
		//! 背景IN
		back_In,
		//! ロゴIN
		logo_In,
		//! ロゴOUT
		logo_Out,
		//! 背景OUT
		back_Out,
		//! 終了
		end,
	};
	//! ロゴ画像のポインタ
	Texture* logo;
	//! ロゴのα値
	float logo_a;
	//! 背景の色
	Color back;
	//! 状態
	Mode mode;
	//! スマートポインタ
	typedef std::shared_ptr<LogoTask> SP;
	/**
	*@brief	:constructor
	*/
	LogoTask();
	/**
	*@brief	:更新処理
	*/
	void UpDate() override;
	/**
	*@brief	:描画処理
	*/
	void Render2D() override;
public:
	/**
	*@brief	:タスク生成
	*@return:失敗した場合nullptr
	*/
	static SP Create();
	/**
	*@brief	:destructor
	*/
	virtual ~LogoTask();
};