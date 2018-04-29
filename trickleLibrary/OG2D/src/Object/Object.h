#pragma once
//______________________________//
//|ゲームオブジェクト            |//
//|履歴：2018/03/20金子翔       |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include <functional>
enum Objform
{
	Non,
	Ball,
	Cube,
};
class Object
{
public:
	Objform objform;
	Vec2 position;
	Vec2 Scale;
	float angle;
	CollisionBox collisionCube;
	CollisionCircle collisionBall;
	bool Gravity;
	float mass;
	float fricition = 0.f;
	float fricition_current = 0.f;
	bool hit(Object o);
	Object();
	Object(Objform form, Vec2 _posi, Vec2 _Sca, float _ang);
	~Object();
	void CreateObject(Objform form, Vec2 _posi, Vec2 _Sca, float _ang);
	std::string objectTag;
	bool isCollided;
	bool isCollidedGlobal = false;

	void LineDraw();

	void SetFricition(float);
	Vec2 UseFricition() const;


	/**
	 * @note 物理処理を使うオブジェクトのなかでこの関数を読んで下さい
	 * @code void Update() { Object::updatePhysics(); .... }
	 */
	void UpdatePhysics();

	/**
	 * @brief オーバーライドして当たり判定処理を書いてください
	 * @param Object このオブジェクトに当たった他のオブジェクト
	 */
	std::function<void(const Object&)> CollisionProcess;

	/**
	 * @brief 当たり判定が終了されるときの最後の１フレームだけ呼び出されます。
	 * @param 当たったオブジェクト
	 */
	std::function<void(const Object&)> CollisionOut;

	/**
	* @brief 当たり判定が始まるときの最後の１フレームだけ呼び出されます。
	* @param 当たったオブジェクト
	*/
	std::function<void(Object&)> CollisionIn;

private:
};