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
		CLEAR,		//クリアの時
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
		NoLower,	//おろせない
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
	const float MOVE_SPEED;								//移動スピード
	//const float JUMP_POWER = -30.f;							//ジャンプパワー(test)
	const float JUMP_POWER;								//ジャンプパワー
	const float MAX_FALL;								//落下最大速度
	const float GRAVITY;		//重力加速度
	const float FIN_SPEED;								//摩擦
	bool CheckJump;												//ジャンプ判定
	bool CheckGravity;											//重力加速度判定
	int moveCnt;												//移動カウント
	Texture* playerimg;											//画像データ
	Vec2 est;													//移動量
	Direction direction;										//向きを格納する変数
	Motion motion;												//現状モーション
	State state;												//現状状態
	GameObject head;
	GameObject foot;
	GameObject left;
	GameObject right;
	Animation animation;										//アニメーションの移動処理
	int inv;													//無敵時間
	std::string taskName;
	bool hold;
	bool isInputAuto;
	bool isInput;
	Vec2 haveAddPos;	//持つ状態の時のposition移動量
private:
	bool HeadCheck();											//頭の当たり判定
	bool FootCheck();											//足元の当たり判定
	bool HeadMapCheck(std::string& objname_,bool = true);			//頭の別オブジェクトへの判定
	bool FootMapCheck(std::string& objname_,bool = false);			//足元の別オブジェクトへの判定
	bool SolidFootCheck();
	bool SolidHitCheck();
	void MoveCheck(Vec2& est);									//移動判定処理
	void LadderMoveCheck(Vec2& est);			//梯子状態で使用する移動処理
	void Friction();											//重力や摩擦の計算
	bool HaveObjectHit();											//バケツとの当たり判定
	void HaveObjectPosMove();											//所持しているバケツの位置を変える
	bool TohaveObjectHit();											//ブロックとの当たり判定
	bool MapHitCheck(std::string& objname_);						//指定したオブジェクトタグのオブジェクトの当たり判定
	void SwitchCheck();											//スイッチとの当たり判定
	bool LadderJumpCheck();										//梯子中にジャンプを行う際の当たり判定
	bool PutCheck();											//置く動作を行えるかの判定
	bool HeadSolidCheck();										//頭上氷判定
	void StateUpDate();
	bool MotionUpDate();
	bool MotionNormalUpDate();
	bool MotionJumpUpDate();
	bool MotionLadderUpDate();
	bool MotionWalkUpDate();
	bool MotionNoLowerUpDate();
	void StateClearUpdate();
	bool LadderCheck();
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
public:
	typedef std::shared_ptr<Player> SP;
	static SP Create(Vec2&, bool = true);
	Player();													//コンストラクタ
	virtual ~Player();											//デストラクタ
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
	bool ReleaseSolid();						//持っている氷の上に氷が当たった時の処理
	void SetMotion(Motion motion_);
	void SetState(State state_);
	void SetInput(bool);
	bool GetInput() const;
};