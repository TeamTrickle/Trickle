#pragma once
//______________________________//
//|動かないギミック 梯子       |//
//|履歴：2018/03/29 横尾	   |//
//|　                          |//
//|____________________________|//
#include "Object.h"
class Ladder : public Object
{
public:
	bool Initialize();
	void UpDate();
	void Render();			//mapで描画を行うのであまり意味がない
	void Finalize();
	Ladder();
	~Ladder();
	//☆☆☆☆//
	//追加変数//
	//☆☆☆☆//
private:
	bool flag;				//Playerと接触をしているかのフラグ
	bool CheakHit();		//Playerとの接触判定を行う
};