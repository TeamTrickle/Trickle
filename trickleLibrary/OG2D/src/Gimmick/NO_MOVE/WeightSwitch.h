#pragma once

/*重さで駆動するスイッチの作成*/
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class WeightSwitch :public GameObject, public TaskObject
{
	float totalmass;        //スイッチに乗っている物の合計質量を格納
	float maxmass;          //扉が開く重さ
	Texture* image;
	std::string taskName;
	Box2D draw;
	Box2D src;
	bool nowActive;             //今扉を開けるかどうか
	bool canPlhitCheck;         //プレイヤと当たり判定をして良いか
	bool canIcehitCheck;        //氷と当たり判定をしてよいか
	bool canBlockhitCheck;      //ブロックと当たり判定をしてよいか
	bool canBuckethitCheck;     //バケツと当たり判定をしてよいか
	float premass;
	std::vector<std::shared_ptr<GameObject>> targets;

	void changeActive();	//自身のオンオフを切り替える(未使用)
	void ToOpen();			//ターゲットを開ける
	void ToClose();			//ターゲットを閉じる

public:
	typedef std::shared_ptr<WeightSwitch> SP;

	explicit WeightSwitch(const Vec2& pos_, const Vec2& size_, const float mass_, std::vector<std::shared_ptr<GameObject>> targets_);      //座標、大きさ、必要な重さ
	virtual ~WeightSwitch();

	//物が乗っているかどうかの状態判断に使う
	enum State
	{
		Nomal,         //乗っていない状態
		Riding         //乗っている状態
	};
	State state;
	GameObject head;       //他のオブジェクトとの当たり判定用

	void UpDate();
	void Render2D();

	void Getmass();
	bool SetnowState();             //今のスイッチの状態を返す
	void SetTexture(Texture*);      //画像のセット
	float SetSwitchUpPos();         //スイッチが元の大きさに戻った時にめり込まないようにする処理
	bool isPushed;                  //一度扉が開いたかどうか
	static SP Create(const Vec2& pos, const Vec2& size, const float mass, std::vector<std::shared_ptr<GameObject>> targets_);
};

