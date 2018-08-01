#pragma once
#include "OGSystem\OGSystem.h"

class LogoTask : public TaskObject
{
	enum Mode
	{
		form1,
		form2,
		form3,
		form4,
		end,
	};
	Texture* logo;
	float logo_a;
	Color back;
	Mode mode;
public:
	typedef std::shared_ptr<LogoTask> SP;
	static SP Create();
	LogoTask();
	virtual ~LogoTask();
	void UpDate() override;
	void Render2D() override;
};