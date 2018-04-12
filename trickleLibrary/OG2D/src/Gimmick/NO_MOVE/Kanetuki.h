//______________________________//
//|動くギミック  加熱機        |//
//|履歴：2018/03/27 横尾	   |//
//|履歴：2018/04/07 横尾       |//
//|____________________________|//
#pragma once
#include "Object\Object.h"
#include "Water\water.h"
#include <vector>

class Kanetuki : public Object
{
public:
	/*
	コンストラクタを呼び出す
	■ 引数   : なし
	■ 戻り値 : なし
	*/
	explicit Kanetuki();


	/*
	コンストラクタを呼び出す
	■ 引数   : Vec2 初期座標値
	■ 戻り値 : なし
	*/
	explicit Kanetuki(Vec2);

	/*
	デストラクタ
	■ 引数   : なし
	■ 戻り値 : なし
	*/
	~Kanetuki();


	/*
	当たり判定矩形の生成やフラグの初期化をします。ラムダ式の当たり判定を呼び出します。
	■ 引数   :
	■ 戻り値 :
	*/
	void Initialize();


	/*
	今回はやることがなし　未実装
	■ 引数   :
	■ 戻り値 :
	*/
	void UpDate();


	/*
	やることなし
	■ 引数   :
	■ 戻り値 :
	*/
	void Finalize();

//追加変数
public:
	Object hitBace[2];                    //当たり判定矩形を生成する
private:
	bool hitflag[2];                      //当たり判定を格納する
	std::vector<Vec2>Pos;                 //引数で貰ってきた座標データを保存する
	int HotCount[2];                      //水蒸気になるまでの時間格納
//追加関数
public:
	/*
	Vectorに座標を保存します。
	■ 引数   : Vec2 保存したい座標値
	■ 戻り値 : なし
	*/
	void Input_Pos(Vec2);

private:
	/*
	水か個体が来たら水蒸気に変更します。
	■ 引数   : なし
	■ 戻り値 : なし
	*/
	void CheakHit();
};