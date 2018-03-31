//______________________________//
//|動くギミック  扇風機        |//
//|履歴：2018/03/29 横尾       |//
//|履歴：2018/03/30 横尾　     |//
//|履歴：2018/03/31 横尾       |//
//|____________________________|//

#pragma once
#include "Object\Object.h"
#include <vector>                                        //ステージによって変化する扇風機の座標を格納するため
//☆☆☆☆//
//判定をしたいギミックを追加する場合はここに記述する//
//☆☆☆☆//

#include "Water\water.h"                                 //水との当たり判定
#include "Switch.h"                                      //スイッチとの当たり判定・Switchの切り替えフラグ

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
	Vec2 Switch_On_or_Off_pos(const Vec2);               //Switchを切り替える時に座標のデータを取得する関数（Vec2　切り替える扇風機の座標値）
private:
	bool Water_flag;                                     //当たり判定格納変数
	bool Switch_Hitflag;                                 //当たり判定格納変数
	bool Switch_ON_OFF;                                  //OFF(false) 上の扇風機　ON(true)　下の扇風機
	CollisionBox range;                                  //視野範囲（現在は使用していません）
	Object* parent;                                      //nullptrCheak関数
	std::vector<Vec2> Pos;                               //コンストラクタで送られたきた座標値を保存する格納倉庫
};