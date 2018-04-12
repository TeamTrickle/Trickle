#pragma once
//______________________________//
//|動くギミック 製氷機         |//
//|履歴：2018/04/07 横尾       |//
//|____________________________|//


#include "Object\Object.h"
#include <vector>

#include "Water\water.h"

class Seihyouki : public Object
{
public:
	/*
	コンストラクタ
	■ 引数   : なし
	■ 戻り値 : なし
	*/
	Seihyouki();


	/*
	コンストラクタ
	■ 引数   : Vec2 初期座標値
	■ 戻り値 : なし
	*/
	Seihyouki(Vec2);


	/*
	デストラクタ
	■ 引数   : なし
	■ 戻り値 : なし
	*/
	virtual ~Seihyouki();


	/*
	オブジェクトタグの設定　オブジェクトの生成　
	■ 引数   : なし
	■ 戻り値 : なし
	*/
	void Initialize();



//追加変数//
public:
	Object hitBace;                      //当たり判定矩形の生成
private:
	std::vector<Vec2> Pos;               //座標値を格納する変数
	int coldCount;                       //氷になるまでの時間を格納する
//追加関数//
public:
	/*
	当たり判定の処理をします
	■ 引数   : なし
	■ 戻り値 : なし
	*/
	void CheakHit();

	/*
	vectorに引数の座標値を追加します
	■ 引数   : Vec2 格納する座標値 
	■ 戻り値 : なし
	*/
	void Input_Pos(Vec2);
};