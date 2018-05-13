#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include <vector>


class UI :public GameObject,public TaskObject {
	Texture tex;
	Vec2 pos;		//座標
	int counter;	//時間はかる。
	int index;		//描画するsrc
	//Box2D src;		//Draw()の第二引数
	int num;		//画像分割数
	int life;		//寿命
	bool active;	//生死
	//bool visible;	//可視不可視
	std::vector<Box2D> srcTable;
	int appeared;	//初期：-1、一度プレイヤと接触したら0、出たら1

public:
	UI();
	~UI();
	typedef std::shared_ptr<UI> SP;
	static SP Create(Vec2&, Box2D&, std::string&, int, int,bool = true);
	
	bool Initialize(Vec2& p, Box2D& coll, std::string& path, int life, int num = 0);	//座標、ファイルパス、寿命、画像分割数
	void UpDate();
	void Move(Vec2 p);		//座標を動かすときに使う
	void Render2D();
	bool Finalize();

	//void Appear();
	//void Vanish();
	//bool CheckHitPlayer();
};