#pragma once

#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Win\WinMain.h"
#include "Map\Map.h"

class Block1 :public Object
{
public:
	Texture BlockImg;
	std::string fileName = "Collision.png";

	float speed;        //ˆÚ“®‘¬“x
	bool hitCheck;

	bool hitR_;
	bool hitL_;
	Box2D hitR;
	Box2D hitL;

	void HitCheckR(Box2D p_);
	void HitCheckL(Box2D p_);

	void Initialize();
	void UpDate();
	void Render();
	void Finalize();
};

class Player1 :public Object
{
public:
	Texture PlImg;
	std::string fileName = "Collision.png";
	bool hitCheck;

	void Initialize();
	void UpDate();
	void Finalize();
	void Render();
};

class Block_ :public Object
{
public:
	void Initialize();
	TaskFlag UpDate();
	void Render();
	void Finalize();

	Player1 pl_;
	Block1 block_;
	Map map;
};



