//______________________________//
//|動くギミック  スイッチ      |//
//|履歴：2018/03/29 横尾	   |//
//|履歴：2018/03/31 横尾　     |//
//|履歴：2018/04/01 横尾       |//
//|____________________________|//
#pragma once
#include "Object.h"
#include "Player\Player.h"
#include <vector>

class Player;

class Switch : public Object
{
public:
	/*
	コンストラクタ　※現在は何も処理がありません
	■ 引数   : なし
	■ 戻り値 : なし
	*/
	explicit Switch();


	/*
	コンストラクタ（Vec2　初期座標値）
	■ 引数   : Vec2 スイッチの初期座標値設定
	■ 戻り値 : なし
	*/
	explicit Switch(Vec2);


	/*
	デストラクタ　Player*をdeleteで削除します。
	■ 引数   : なし
	■ 戻り値 : なし
	*/
	virtual ~Switch();
	
	
	/*
	(引数1 初期座標)初期化処理　当たり判定・矩形の生成・フラグの初期化
	■ 引数   : Vec2 初期化座標値
	■ 戻り値 : bool 初期化成功したかを返します。（現状trueしか入りません）
	*/
	bool Initlaize(Vec2);
	

	/*
	更新処理
	■ 引数   : なし
	■ 戻り値 : なし
	*/
	void UpDate();
	

	/*
	解放処理
	■ 引数   : なし
	■ 戻り値 : なし
	*/
	void Finalize();


	/*
	描画処理（今のところ意味がない）
	■ 引数   : なし
	■ 戻り値 : なし
	*/
	void Render();


	/*
	当たり判定の処理を書いたところ
	■ 引数   : なし
	■ 戻り値 : なし
	*/

	void CheakHit();


	/*
	nullptrでないか調べる関数
	■ 引数   : なし
	■ 戻り値 : bool
	*/
	bool HasParent() const;


	/*
	メンバ変数 parentに引数のPlayer*を当てる（Player* 代入するObject*)
	■ 引数   : Player* Playerのクラスのアドレス値
	■ 戻り値 : なし
	*/
	void SetParent(Player* obj);
private:
	bool Hitflag;                                //当たり判定
	bool switch_ON_OFF;                          //スイッチがONかOFFかを示す ON(true) OFF(false)
	std::vector<Vec2>Pos;                        //コンストラクタ時に引数できた座標値を保存する
	Player* player_pointa;                       //Playerのアドレス値を取得して当たり判定を実装に必要
};