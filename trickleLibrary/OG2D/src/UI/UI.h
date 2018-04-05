#pragma once
#include "OGSystem\OGsystem.h"


class UI {
	Texture tex;
	Vec2 pos;		//座標
	int counter;	//時間はかる。
	Box2D src;		//Draw()の第二引数
	int num;		//画像分割数
	int life;		//寿命
	bool active;	//生死

public:
	UI();
	~UI();


	void Initialize(Vec2 p, std::string path, int num, int life);	//座標、ファイルパス、画像分割数
	void Update();
	void Move(Vec2 p);		//座標を動かすときに使う
	void Render();
	void Finalize();
};