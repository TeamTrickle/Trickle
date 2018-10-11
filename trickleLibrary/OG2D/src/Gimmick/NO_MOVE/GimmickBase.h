/**
* @file GimmickBase.h
* @brief Fan,Heater,Icemachineの基底クラスを定義する
* @author yokota0717
* @date 2018.10.9
*/

#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

/**
* @brief Fan,Heater,Icemachineの基底クラス
* @details スイッチでオンオフを切り替えるギミックはこのクラスを継承すること
*/
class GimmickBase : public GameObject, public TaskObject
{
public:
	/**
	* @brief ギミックの向き
	*/
	enum Dir {
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};

private:
	//! @brief 登録するタスク名
	std::string taskName_;
	//! @brief 水と当たり判定を行う矩形
	GameObject hitBase_;
	//! @brief 自身の駆動状態
	bool active_;
	//! @brief 本体の向き
	Dir dir_;
	//! @brief 当たり判定の幅
	Vec2 range_;


public:
	GimmickBase(Vec2 pos, Vec2 range, Dir dir, bool active);
	~GimmickBase();

	/**
	* @brief タスクオブジェクト生成窓口
	* @param pos ギミックの本体を表示する座標(画像左上)
	* @param range 当たり判定矩形の大きさ
	* @param dir 本体の向き
	* @param active 生成した時点で動いているかどうか
	*/
	std::shared_ptr<GimmickBase> Create(Vec2 pos, Vec2 range, Dir dir, bool active);

	/**
	* @brief 初期化処理
	*/
	virtual bool Initialize(Vec2 pos, Vec2 range, Dir dir, bool active);

	/**
	* @brief タスク名を登録する
	*/
	void setTaskName(const std::string& name);

	/**
	* @brief 当たり判定矩形を設定する
	*/
	void setHitBase(Vec2 pos, Vec2 range);
	/**
	* @brief 当たり判定矩形を返す
	*/
	GameObject getHitBase();

	/**
	* @brief 自身の稼働状態を反転させる
	*/
	void changeActive();

	/**
	* @brief ある状態の水に効果を与える
	* @details Fan：水蒸気を横に動かす、Heater：氷→水,水→水蒸気、Icemachine：水→氷
	*/
	virtual void affectWater();

	/**
	* @brief 向きを設定する
	*/
	void setDirection(Dir d);
	/**
	* @brief 向きを返す
	*/
	Dir getDirection();

	/**
	* @brief 駆動状態を設定する
	*/
	void setActive(bool a);

	/**
	* @brief 駆動状態を返す
	*/
	bool isActive();
};

