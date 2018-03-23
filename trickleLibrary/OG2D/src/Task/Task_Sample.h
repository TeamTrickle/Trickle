#pragma once
//______________________________//
//|サンプルタスク               |//
//|履歴：2018/03/20金子翔       |//
//|____________________________|//
#include "Win\WinMain.h"
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
class ObjectSample :public Object{
public:
	//Object object;
	Texture sampleimg;
	std::string fileName = "Collision.png";
	bool hitcheck;
	void Initialize();
	void UpDate();
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
	void UpDate();
	void Render();
	void Finalize();
};
class Sample
{
public:
	void Initialize();
	TaskFlag UpDate();
	void Render2D();
	void Finalize();
	//☆☆☆☆//
	//追加変数//
	//☆☆☆☆//
	ObjectSample objsmp;
	ObjectSample2 objsmp2;
};