//ジャスティン風

//|動くギミック  扇風機        |//
//|履歴：2018/03/29 横尾       |//
//|履歴：2018/03/30 横尾　     |//
//|履歴：2018/03/31 横尾       |//
//|履歴：2018/04/01 横尾       |//
//|履歴: 2018/04/02 横尾       |//
//|履歴: 2018/04/03 横尾       |//
//|履歴：2018/04/06 横尾       |//
//|履歴：2018/04/07 横尾       |//
//|____________________________|//

//#pragma once
//#include "Object\Object.h"
//#include <vector>                                        //ステージによって変化する扇風機の座標を格納するため
////☆☆☆☆//
/////判定をしたいギミックを追加する場合はここに記述する///
////☆☆☆☆//
//
//#include "Water\water.h"                                 //水との当たり判定
//#include "Switch.h"                                      //スイッチとの当たり判定・Switchの切り替えフラグ
//#include "Map\Map.h"                                     //Mapとの判定
//
//class Map;
//class Switch;
//
//class Senpuki : public Object
//{
//public:
//	/*
//	初期座標によって当たり判定矩形の生成・フラグの初期化・ラムダ式の当たり判定を行います。
//	■ 引数   : Vec2 初期化座標値
//	■ 戻り値 : bool 初期化成功したかを返します。（現状trueしか入りません）
//	*/
//	bool Initialize(Vec2);
//
//
//
//	/*
//	扇風機の更新処理
//	■ 引数   : なし
//	■ 戻り値 : なし
//	*/
//	void UpDate();
//
//
//
//	/*
//	扇風機の解放処理
//	■ 引数   : なし
//	■ 戻り値 : なし
//	*/
//	void Finalize();
//
//
//
//	/*
//	扇風機の描画処理（Mapで表示するのであまり意味がない）
//	■ 引数   : なし
//	■ 戻り値 : なし
//	*/
//	void Render();
//
//
//
//	/*
//	コンストラクタ　※何もすることありません
//	■ 引数   : なし
//	■ 戻り値 : なし
//	*/
//	explicit Senpuki();
//
//
//
//	/*
//	コンストラクタ（Vec2　初期座標)
//	■ 引数   : Vec2 扇風機の初期座標に設定する座標値
//	■ 戻り値 : なし
//	*/
//	explicit Senpuki(Vec2);
//
//
//
//	/*
//	デストラクタ　Object*をdeleteで削除します。
//	■ 引数   : なし
//	■ 戻り値 : なし
//	*/
//	virtual ~Senpuki();
//
//
//
//	/*
//	Object* parent の指している場所がnullptrではないかをbool型で返します。
//	■ 引数   : なし
//	■ 戻り値 : bool
//	*/
//	bool HasParent() const;
//
//
//	/*
//	Swtich* 当たり判定に必要なクラスのアドレス値を代入します。
//	■ 引数   : Switch* 当たり判定に必要なクラスのアドレス値  int スイッチの配列要素値
//	■ 戻り値 : なし
//	*/
//	void SetParent(Switch*, int);
//
//
//	/*
//	Object* 当たり判定に必要なクラスのアドレス値を代入します。
//	■ 引数   : Object* 当たり判定に必要なクラスのアドレス値
//	■ 戻り値 : なし
//	*/
//	void SetParent(Object*);
//
//
//	/*
//	Map* 当たり判定に必要なクラスのアドレス値を代入します。
//	■ 引数   : Map* 当たり判定に必要なクラスのアドレス値
//	■ 戻り値 : なし
//	*/
//	void SetParent(Map*);
//
//
//	/*
//	当たり判定をまとめた関数です。（初期化処理->ラムダ式の当たり判定の場所で採用）
//	■ 引数   : なし
//	■ 戻り値 : なし
//	*/
//	void CheakHit();
//
//
//	/*
//	スイッチの切り替えフラグがあった場合に扇風機の座標を切り替えます。
//	■ 引数   : const Vec2 切り替わる場所の座標値
//	■ 戻り値 : Vec2
//	*/
//	Vec2 Switch_On_or_Off_pos(const Vec2);
//
//
//	/*
//	vectorに座標値を代入する関数です。
//	■ 引数   : Vec2 vectorにセット追加したい当たり判定座標値
//	■ 戻り値 : なし
//	*/
//	void Set_Pos(Vec2);
//
//
//	/*
//	スイッチの切り替えフラグによって座標値の再設定をします。
//	■ 引数   : Switch* Sキー（切り替えボタン）が押されたら即座にそのSwitchの切り替えフラグを見て扇風機の稼働するオブジェクトを変更します。
//	■ 戻り値 : なし
//	*/
//	void Switch_Swap(Switch*, int);
//
//	/*
//	水蒸気状態になったときに扇風機によって移動をします。
//	■ 引数   : Object& 水蒸気状態になった水のアドレス値
//	■ 戻り値 : Vec2 移動するべき移動量
//	*/
//	Vec2 Water_Move(Object&);
//
//	/*
//	水との当たり判定をチャックします
//	■ 引数   : const Object& 水のアドレス値
//	■ 戻り値 : bool 視野範囲と当たっているかを返す
//	*/
//	bool Cheak_Water(const Object&);
//
//private:
//	bool Water_flag;                                     //当たり判定格納変数
//	bool Switch_ON_OFF;                                  //OFF(false) 上の扇風機　ON(true)　下の扇風機
//	bool Wall_flag;                                      //壁との当たり判定フラグ格納する変数
//	bool Range_Flag;                                     //視野範囲との当たり判定を格納する
//	Map* parent_Wall;                                    //nullptrCheak関数(今回は壁)
//	std::vector<Vec2> Pos;                               //コンストラクタで送られたきた座標値を保存する格納倉庫
//	Switch* switch_pointa[2];                            //switchのアドレス値を格納する変数
//public:
//	Object range;                                        //視野範囲（現在は使用していません）
//};


//横田さん風

#pragma once
#include "Object\Object.h"
#include "Win\WinMain.h"
#include "Gimmick\NO_MOVE\Switch.h"
#include "Water\water.h"
#include <vector>

class Switch;

class Fan :public Object {
	std::vector<Switch*> switches;		//自身の稼働にかかわっているスイッチ一覧
public:
	enum Dir {
		LEFT,
		RIGHT,
	};

	void Initialize(Vec2 pos, float r, Dir d, bool activ);
	void AddSwitch(Switch* swit);
	void ChangeState();
	void Finalize();
	void Render();
private:
	Dir dir;
	Texture image;
	float range;
	float strength;
	bool active;


};

