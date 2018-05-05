#pragma once
#include "OGSystem\OGsystem.h"
#include <vector>


class UI {
	Texture tex;
	Vec2 pos;		//座標
	int counter;	//時間はかる。
	int index;		//描画するsrc
	//Box2D src;		//Draw()の第二引数
	int num;		//画像分割数
	int life;		//寿命
	bool active;	//生死
	std::vector<Box2D> srcTable;

public:
	UI();
	~UI();

	
	void Initialize(Vec2 p, std::string path, int life, int num = 0);	//座標、ファイルパス、寿命、画像分割数
	void Update();
	void Move(Vec2 p);		//座標を動かすときに使う
	void Render();
	void Finalize();

};