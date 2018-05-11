#pragma once
//______________________________//
//|プレイヤ                    |//
//|履歴：2018/03/23横田	       |//
//|履歴：2018/03/26劉韋君　    |//
//|履歴：2018/03/29劉韋君　    |//
//|履歴：2018/03/30木務　    |//
//|____________________________|//
#include "Bucket\bucket.h"
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Gimmick\NO_MOVE\Switch.h"
#include "Block\block.h"

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
	enum State
	{
		NORMAL,		//通常
		LADDER,		//はしご中
		BUCKET,		//バケツ所持
		ANIMATION,	//アニメーション中
	};
	enum Motion
	{
		Normal,		//通常
		Walk,
		Jump,		//ジャンプ
		Ladder,		//はしご
		Fall,		//落下
	};
	class Animation
	{
	public:
		Vec2 animationVec;										//移動量
		Vec2 startVec;											//開始位置
		Vec2 endVec;											//終了位置
		int timeCnt;											//アニメーション経過時間
		//int idle[10];											//Normal状態のアニメーション
	public:
		void SetAnimaVec(Vec2& start_, Vec2& end_);				//開始位置と終了位置を登録
		bool Initialize();										//初期化
		Vec2 Move();											//移動処理を行い移動値を返す
		bool isMove();											//移動処理中かどうかを返す
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
	std::vector<GameObject*> objects;								//当たり判定オブジェクト
	std::vector<Bucket*> buckets;								//バケツ判定
	std::vector<Block*> blocks;									//ブロック判定
	std::vector<GameObject*> waters;								//水判定
	Bucket* haveBucket;											//所持バケツ情報
	Animation animation;										//アニメーションの移動処理
	int inv;													//無敵時間
	std::string taskName;
private:
	bool HeadCheck();											//頭の当たり判定
	bool FootCheck();											//足元の当たり判定
	bool HeadCheck(std::string& objname_, int n = 0);			//頭の別オブジェクトへの判定,0 = そのオブジェクト,1 = それ以外のオブジェクト
	bool FootCheck(std::string& objname_, int n = 0);			//足元の別オブジェクトへの判定
	void MoveCheck(Vec2& est);									//移動判定処理
	void MoveCheck(Vec2& est, std::string& objname_);				//梯子状態で使用する移動処理
	void Friction();											//重力や摩擦の計算
	bool BucketHit();											//バケツとの当たり判定
	void BucketMove();											//所持しているバケツの位置を変える
	bool BlockHit();											//ブロックとの当たり判定
	bool ObjectHit(std::string& objname_);						//指定したオブジェクトタグのオブジェクトの当たり判定
public:
	typedef std::shared_ptr<Player> SP;
	static SP Create(Vec2&, bool = true);
	Player();													//コンストラクタ
	virtual ~Player();													//デストラクタ
	bool Initialize();											//初期化
	bool Initialize(Vec2&);										//位置設定初期化
	void UpDate();												//更新処理
	void Render2D();												//描画処理
	bool Finalize();											//解放処理
	void AddObject(GameObject* obj_);								//オブジェクトを登録する
	void DeleteObject(GameObject* obj_);							//指定オブジェクトを登録から削除する
	void AllDelete();											//全登録オブジェクトの削除
	void AddBucket(Bucket* bucket);								//バケツオブジェクトの登録
	bool DeleteBucket(Bucket* bucket);							//指定バケツオブジェクトを削除
	void AddBlock(Block* block);								//ブロックオブジェクトを登録	
	bool DeleteBlock(Block* block);								//指定ブロックオブジェクトの削除
	void AddWater(GameObject*);										//水オブジェクトを登録
	bool DeleteWater(GameObject*);									//指定水オブジェクトの削除
	Vec2 GetEst() const;										//現在移動値を返す
	void SetTexture(Texture* texture);							//テクスチャを登録
	State NowState() const;										//現在のStateを返す
	void SetPos(Vec2&);											//プレイヤーの位置を設定する
	Vec2 GetPos() const;										//プレイヤーの位置を返す
	//入力処理簡略化
	bool InputLeft() {
		return OGge->in->on(Input::CL);
	}
	bool InputRight() {
		return OGge->in->on(Input::CR);
	}
	bool InputDown() {
		return OGge->in->on(Input::CD);
	}
	bool InputUp() {
		return OGge->in->on(Input::CU);
	}
};