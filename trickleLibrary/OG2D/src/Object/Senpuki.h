//______________________________//
//|動くギミック  扇風機        |//
//|履歴：2018/03/29 横尾       |//
//|履歴：2018/03/30 横尾　     |//
//|履歴：2018/03/31 横尾       |//
//|____________________________|//

#pragma once
#include "Object\Object.h"

//☆☆☆☆//
//判定をしたいギミックを追加する場合はここに記述する//
//☆☆☆☆//

#include "Water\water.h"                                 //水との当たり判定

class Senpuki : public Object
{
public:
	bool Initialize(Vec2);                               //初期化をするところ(Vec2 初期座標)
	void UpDate();                                       //扇風機の更新処理
	void Finalize();                                     //扇風機の解放処理
	void Render();                                       //扇風機の描画処理（Mapで表示するのであまり意味がない）
	explicit Senpuki();                                  //コンストラクタ（引数　なし）
	explicit Senpuki(Vec2 pos);                          //コンストラクタ（Vec2　初期座標)
	virtual ~Senpuki();                                  //デストラクタ　何もすることなし
	bool HasParent() const;                              //nullptrでないか調べる関数
	void SetParent(Object* obj);                         //メンバ変数 parentに引数のObject*を当てる（Object* 代入するObject*)
	void CheakHit();                                     //当たり判定の処理をまとめた関数（現在はPlayer）実際は水で処理をします。
private:
	bool flag;                                           //当たり判定格納変数
	CollisionBox range;                                  //視野範囲（現在は使用していません）
	Object* parent;                                      //nullptrCheak関数
};