#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Chara : public GameObject, public TaskObject
{
public:
	enum Direction						//向きを管理
	{
		LEFT,
		RIGHT,
	};
private:
	Texture Image;		//使用画像
	Vec2 move;			//移動値
	const float MOVE_SPEED;								//移動スピード
	const float JUMP_POWER;								//ジャンプパワー
	const float MAX_FALL;								//落下最大速度
	const float GRAVITY;		//重力加速度
	const float FIN_SPEED;								//摩擦
	Direction direction;										//向きを格納する変数
	std::string taskName;										//名
	int AnimCnt;			//アニメーションカウント
	bool isAuto;			//オート状態有無
	bool isCollision;		//当たり判定有無
	int MoveCnt;			//移動カウント
	__int8 isCollisionNow;	//当たり判定状態カウント
	bool isAutoOff;			//オートモード移行有無
	bool isAutoMode;		//オートモードでの移動指定有無
	Vec2 startPos;			//オートモード時の開始地点
	Vec2 EndPos;			//オートモード時の終了地点
	Easing easing_x;		//イージング移動値
public:
	Chara(std::string&, Vec2&);	//コンストラクタ
	virtual ~Chara();			//デストラクタ
	typedef std::shared_ptr<Chara> SP;
	static SP Create(std::string&, Vec2&, bool = true);
	void UpDate();		//更新処理
	void Render2D();	//描画処理
	void Friction(Vec2&);	//重力処理
	void MoveCheck(Vec2);	//移動処理
	bool FootCheck();		//足元チェック
	bool Jump();			//ジャンプを行う
	void AutoMove();		//オート移動
	void ManualMove(Vec2&);	//手動移動
	void IsCollisionCheck();	//当たり判定カウントを増やす
	bool CollisionNumCheck(__int8);	//当たり判定カウントが引数と同じかを返す
	void MoveReset();				//移動値を初期化させる
	void SetDirection(const Direction&);	//向きを強制変更させる
	void SetAutoFlag(const bool);			//オート移動を行うかを設定
	void SetAutoMode(const bool);			//オート処理を任意のものかを設定
	Vec2 GetMove() const;					//移動値を返す
	void Set(const Vec2&, const Vec2&);		//開始位置と終了位置を登録する
	bool isAutoPlay() const;				//オート移動を行っているかを返す
	Direction nowDirection() const;			//現在の向きを返す
};