#pragma once
#include "OGSystem\OGSystem.h"

class LogoTask : public TaskObject
{
	/**
	*enum Mode
	*σΤΗ
	*/
	enum Mode
	{
		//! wiIN
		back_In,
		//! SIN
		logo_In,
		//! SOUT
		logo_Out,
		//! wiOUT
		back_Out,
		//! IΉ
		end,
	};
	//! SζΜ|C^
	Texture* logo;
	//! SΜΏl
	float logo_a;
	//! wiΜF
	Color back;
	//! σΤ
	Mode mode;
	//! X}[g|C^
	typedef std::shared_ptr<LogoTask> SP;
	/**
	*@brief	:constructor
	*/
	LogoTask();
	/**
	*@brief	:XV
	*/
	void UpDate() override;
	/**
	*@brief	:`ζ
	*/
	void Render2D() override;
public:
	/**
	*@brief	:^XNΆ¬
	*@return:Έs΅½κnullptr
	*/
	static SP Create();
	/**
	*@brief	:destructor
	*/
	virtual ~LogoTask();
};