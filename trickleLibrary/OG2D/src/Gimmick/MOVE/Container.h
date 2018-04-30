#pragma once

#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Win\WinMain.h"

class Youki :public Object
{
public:
	Texture ContainerImg;
	std::string fileName = "Collision.png";

	float water;        //入ってる水の量0.0f~1.0f
	float speed;        //移動速度
	bool hold;          //プレイヤがもっているかどうかの判定
	bool hitCheck;

	void CreateNew(Box2D pos);      //オブジェクトを生成

	void Initialize();
	void UpDate();
	void Render();
	void Finalize();
};

//class Player :public Object
//{
//public:
//	Texture PlImg;
//	std::string fileName = "Collision.png";
//	bool hitCheck;
//
//	void Initialize();
//	void UpDate();
//	void Finalize();
//	void Render();
//};

class Container_ :public Object
{
public:
	void Initialize();
	//TaskFlag UpDate();
	void UpDate();
	void Render();
	void Finalize();

	//Player pl_;
	Youki youki_;
};

