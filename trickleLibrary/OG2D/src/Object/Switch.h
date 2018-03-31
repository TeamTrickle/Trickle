//______________________________//
//|動くギミック  スイッチ      |//
//|履歴：2018/03/29 横尾	   |//
//|履歴：2018/03/31 横尾　     |//
//|____________________________|//
#pragma once
#include "Object.h"
#include "Player\Player.h"
#include <vector>

class Player;

class Switch : public Object
{
public:
	explicit Switch();                           //コンストラクタ（引数なし）
	explicit Switch(Vec2);                       //コンストラクタ（Vec2　初期座標値）
	virtual ~Switch();                           //デストラクタ　現在は特になし
	bool Initlaize(Vec2);                        //(引数1 初期座標)初期化処理　当たり判定・矩形の生成・フラグの初期化
	void UpDate();                               //更新処理
	void Finalize();                             //解放処理
	void Render();                               //描画処理（今のところ意味がない）

	void CheakHit();                             //当たり判定の処理を書いたところ
	bool HasParent() const;                      //nullptrでないか調べる関数
	void SetParent(Player* obj);                 //メンバ変数 parentに引数のPlayer*を当てる（Player* 代入するObject*)
private:
	bool Hitflag;                                //当たり判定
	bool switch_ON_OFF;                          //スイッチがONかOFFかを示す ON(true) OFF(false)
	std::vector<Vec2>Pos;                        //コンストラクタ時に引数できた座標値を保存する
	Player* player_pointa;                       //Playerのアドレス値を取得して当たり判定を実装に必要
};