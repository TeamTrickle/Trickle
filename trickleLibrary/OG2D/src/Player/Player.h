#pragma once
//______________________________//
//|プレイヤ                    |//
//|履歴：2018/03/23横田	       |//
//|履歴：2018/03/26劉韋君　    |//
//|履歴：2018/03/29劉韋君　    |//
//|履歴：2018/03/30木務　    |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Player :public GameObject ,public TaskObject
{
	enum Direction						//向きを管理
	{
		LEFT,
		RIGHT,
	};
	/*const std::array<std::string, 3> WALKABLE_CHIPS{
		"Floor",
		"Soil",
		"Net"
	};*/
public:
	enum State
	{
		NORMAL,		//通常
		BUCKET,		//バケツ所持
		ANIMATION,	//アニメーション中
	};
	enum Motion
	{
		Normal,		//通常
		Walk,		//歩き中
		Jump,		//ジャンプ
		Ladder,		//はしご
		Fall,		//落下
		Switch_M,	//スイッチ操作
		Block_M,	//ブロック押し
		Lift,		//持ちあげる
		Lower,		//持ちおろす
		Spill,		//溢す
	};
private:
	class Animation
	{
	public:
		Vec2 animationVec;										//移動量
		Vec2 startVec;											//開始位置
		Vec2 endVec;											//終了位置
		int timeCnt;											//アニメーション経過時間
		int animCnt;											//リセットされるアニメーションのカウント（スイッチ、梯子、持ちあげる）
		Motion animMo;											//移動するanimation関数をスイッチと梯子両方で使っていて作った変数, アニメーション中に動かないようにすることもやってる
		int same_flag;											//移動する座標とプレイヤの座標が同じときtrueを返す

		int idle[10] = { 0,0,0,0,0,0,0,1,1,1 };					//Normal状態のアニメーション
		int walk[9] = { 0,1,2,3,4,5,6,7,8 };					//Walk状態のアニメーション
		int ladder[2] = { 0,1 };								//ladder_ani状態のアニメーション
		int switch_1[6] = { 0,1,2,3,4 };
		int switch_2[6] = { 4,3,2,1,0 };
		int lift[2] = { 2,3 }; 
		int lower[2] = { 3,2 };
		int spill[3] = { 0, 1, 0 };
	public:
		void SetAnimaVec(Vec2& start_, Vec2& end_);				//開始位置と終了位置を登録
		bool Initialize();										//初期化
		Vec2 Move(Motion motion_);								//移動処理を行い移動値を返す
		bool isMove();											//移動処理中かどうかを返す
		Box2D returnSrc(Motion motion, State state, Direction dir);			//motionによってsrcを返す
	private:
		int srcX = 586, srcY = 575;									//プレイヤ画像の元々のサイズ
	};
private:
	const float MOVE_SPEED = 5.f;								//移動スピード
	//const float JUMP_POWER = -30.f;							//ジャンプパワー(test)
	const float JUMP_POWER = -13.f;								//ジャンプパワー
	const float MAX_FALL = 15.f;								//落下最大速度
	const float GRAVITY = (9.8f / 60.f / 60.f * 32) * 10;		//重力加速度
	const float FIN_SPEED = 0.5f;								//摩擦
	bool CheckJump;												//ジャンプ判定
	bool CheckGravity;											//重力加速度判定
	int moveCnt;												//移動カウント
	Texture* playerimg;											//画像データ
	Vec2 est;													//移動量
	Direction direction;										//向きを格納する変数
	Motion motion;												//現状モーション
	State state;												//現状状態
	Animation animation;										//アニメーションの移動処理
	int inv;													//無敵時間
	std::string taskName;
	bool hold;
	bool isInputAuto;
private:
	bool HeadCheck();											//頭の当たり判定
	bool FootCheck();											//足元の当たり判定
	bool HeadCheck(std::string& objname_, int n = 0);			//頭の別オブジェクトへの判定,0 = そのオブジェクト,1 = それ以外のオブジェクト
	bool FootCheck(std::string& objname_, int n = 0);			//足元の別オブジェクトへの判定
	bool SolidFootCheck();
	void MoveCheck(Vec2 est);									//移動判定処理
	void MoveCheck(Vec2& est, std::string& objname_);			//梯子状態で使用する移動処理
	void Friction();											//重力や摩擦の計算
	bool BucketHit();											//バケツとの当たり判定
	void BucketMove();											//所持しているバケツの位置を変える
	bool TohaveObjectHit();											//ブロックとの当たり判定
	bool ObjectHit(std::string& objname_);						//指定したオブジェクトタグのオブジェクトの当たり判定
	void SwitchCheck();											//スイッチとの当たり判定
	bool LadderJumpCheck();										//梯子中にジャンプを行う際の当たり判定
	bool PutCheck();											//置く動作を行えるかの判定
	bool HeadSolidCheck();										//頭上氷判定
public:
	typedef std::shared_ptr<Player> SP;
	static SP Create(Vec2&, bool = true);
	Player();													//コンストラクタ
	virtual ~Player();											//デストラクタ
	bool Initialize();											//初期化
	bool Initialize(Vec2&);										//位置設定初期化
	void UpDate();												//更新処理
	void Render2D();											//描画処理
	bool Finalize();											//解放処理
	Vec2 GetEst() const;										//現在移動値を返す
	void SetTexture(Texture* texture);							//テクスチャを登録
	State NowState() const;										//現在のStateを返す
	void SetPos(Vec2&);											//プレイヤーの位置を設定する
	Vec2 GetPos() const;										//プレイヤーの位置を返す
	void SetInputAuto(bool);
	bool GetInputAuto() const;
	bool ReleaseHold();
	void SetMotion(Motion motion_);
	//入力処理簡略化
	bool InputLeft();
	bool InputRight();
	bool InputDown();
	bool InputUp();
	bool InputB1down();
	bool InputB2down();
	bool InputB1on();
	bool InputB2on();
	float AxisLX();
	float AxisLY();
	float AxisRX();
	float AxisRY();
};