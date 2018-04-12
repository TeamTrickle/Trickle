//______________________________//
//|動くギミック  スイッチ      |//
//|履歴：2018/03/29 横尾	   |//
//|履歴：2018/03/31 横尾　     |//
//|履歴：2018/04/01 横尾       |//
//|履歴: 2018/04/02 横尾       |//
//|履歴: 2018/04/03 横尾       |//
//|履歴：2018/04/07 横尾       |//
//|____________________________|//
#pragma once
#include "Object\Object.h"
#include "Player\Player.h"
#include "Senpuki.h"
#include <vector>

//class Player;
//class Senpuki;
//
//class Switch : public Object
//{
//public:
//	/*
//	コンストラクタ　※現在は何も処理がありません
//	■ 引数   : なし
//	■ 戻り値 : なし
//	*/
//	explicit Switch();
//
//
//	/*
//	コンストラクタ（Vec2　初期座標値）
//	■ 引数   : Vec2 スイッチの初期座標値設定
//	■ 戻り値 : なし
//	*/
//	explicit Switch(Vec2);
//
//
//	/*
//	デストラクタ　なし
//	■ 引数   : なし
//	■ 戻り値 : なし
//	*/
//	virtual ~Switch();
//
//
//	/*
//	(引数1 初期座標)初期化処理　当たり判定・矩形の生成・フラグの初期化
//	■ 引数   : なし
//	■ 戻り値 : なし
//	*/
//	void Initlaize();
//
//
//	/*
//	更新処理
//	■ 引数   : なし
//	■ 戻り値 : なし
//	*/
//	void UpDate();
//
//
//	/*
//	解放処理
//	■ 引数   : なし
//	■ 戻り値 : なし
//	*/
//	void Finalize();
//
//
//	/*
//	描画処理（今のところ意味がない）
//	■ 引数   : なし
//	■ 戻り値 : なし
//	*/
//	void Render();
//
//
//	/*
//	当たり判定の処理を書いたところ
//	■ 引数   : なし
//	■ 戻り値 : なし
//	*/
//
//	void CheakHit();
//
//
//	/*
//	スイッチの当たり判定座標値をvectorで保存する関数
//	■ 引数   : const Vec2 当たり判定に必要な座標値
//	■ 戻り値 : なし
//	*/
//	void Set_Pos(const Vec2);
//
//public:
//
//	bool switch_ON_OFF[2];                       //スイッチがONかOFFかを示す ON(true) OFF(false)
//	Object hitBace[2];                           //スイッチの当たり判定矩形
//private:
//
//	bool Hitflag;                                //当たり判定
//	std::vector<Vec2>Pos;                        //コンストラクタ時に引数できた座標値を保存する
//};


//横田さん風

//注意！！！！
//プレイヤが二つ以上のスイッチに同時に接触するとエラー吐きます
//必ずスイッチを複数置くときは１マス以上離して配置
class Switch :public Object {
public:	
	void Initialize(Vec2 pos);
	void Update();
	void Finalize();
	void Render();
	bool isON();
	void ON_OFF();
	void SetTarget(Object* t);
private:
	std::vector<Object*> targets;
	Texture image;
	std::string path;
	bool is_on;

};