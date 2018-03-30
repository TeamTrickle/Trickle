#pragma once
//______________________________//
//|背景タスク　　               |//
//|履歴：2018/03/20金子翔       |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Back : public Object {
public:
	Texture backimg;
	std::string fileName = "back.png";

	void Initialize();
	void UpDate();
	void Render();
	void Finalize();
};