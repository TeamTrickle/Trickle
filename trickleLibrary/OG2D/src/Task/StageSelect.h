#pragma once
#include "Win\WinMain.h"
#include "OGSystem\OGsystem.h"

class StageSelect
{
public:
	void Initialize();
	TaskFlag UpDate();
	void Render();
	void Finalize();
};