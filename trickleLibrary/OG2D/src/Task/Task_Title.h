#pragma once
//______________________________//
//|タイトルタスク               |//
//|履歴：2018/03/20金子翔       |//
//|____________________________|//
#include "Win\WinMain.h"
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Map\Map.h"
#include "CollisionManager\CollisionManager.h"
class ObjectSample :public Object{
public:
	//Object object;
	Texture sampleimg;
	std::string fileName = "Collision.png";
	Object footHit;
	Object toolHit;
	bool hitcheck;
	void Initialize();
	void Update();
	void Render();
	void Finalize();
};
class ObjectSample2 :public Object {
public:
	//Object object;
	Texture sampleimg;
	std::string fileName = "Collision.png";
	bool hitcheck;
	void Initialize();
	void Update();
	void Render();
	void Finalize();
};
class Title
{
public:
	void Initialize();
	TaskFlag Update();
	void Render2D();
	void Finalize();
	//☆☆☆☆//
	//追加変数//
	//☆☆☆☆//
	CollisionManager cm;
	ObjectSample objsmp;
	ObjectSample2 objsmp2;
	Map map;
	Sound sound;
};