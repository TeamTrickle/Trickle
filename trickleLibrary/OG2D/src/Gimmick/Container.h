#pragma once

#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Win\WinMain.h"

class GimmickC :public Object
{
public:
	Texture ContainerImg;
	std::string fileName = "Collision.png";
	float water;        //入ってる水の量
	float speed;        //移動速度
	bool hold;          //playerが容器を持っているか
	bool hitRight;
	bool hitLeft;
	bool hitBottom;

	void Initialize();
	TaskFlag UpDate();
	void Render();
	void Finalize();
};

